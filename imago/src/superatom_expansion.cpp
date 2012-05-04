#include "boost/foreach.hpp"
#include "boost/algorithm/string.hpp"

#include "superatom_expansion.h"

#include "indigo.h"

#include "molecule.h"
#include "output.h"
#include "molfile_saver.h"

namespace imago
{

class Abbreviation
{
public:
   std::string name, expansion;
   std::vector<std::string> labels;

   Abbreviation (const std::string &name, const std::string &expansion) : name(name), expansion(expansion)
   {
   }

   Abbreviation& onleft(const std::string &label)
   {
      labels.push_back(label);
      return *this;
   }
   Abbreviation& onright(const std::string &label)
   {
      labels.push_back(label);
      return *this;
   }
   Abbreviation& onleft(const std::string &label1, const std::string &label2)
   {
      onleft(label1);
      onleft(label2);
      return *this;
   }
   Abbreviation& onright(const std::string &label1, const std::string &label2)
   {
      onright(label1);
      onright(label2);
      return *this;
   }
};

std::string expandSuperatoms( const Molecule &molecule )
{
   using namespace std;

   static bool init = false;
   static std::vector<Abbreviation> abbrs;
   typedef pair<int, int> pair_i_i;

   if (!init)
   {
      abbrs.push_back(Abbreviation("TfO", "FC(F)(F)S(=O)(=O)O*").onright("OTf").onleft("TfO"));
      abbrs.push_back(Abbreviation("COOEt", "CCOC(*)=O").onright("COOEt").onleft("EtOOC"));
      abbrs.push_back(Abbreviation("SiPr", "CC(C)S*").onright("SiPr", "Si-Pr").onleft("iPrS", "i-PrS"));
      abbrs.push_back(Abbreviation("iPrO", "CC(C)O*").onright("OiPr", "Oi-Pr").onleft("iPrO", "i-PrO"));
      abbrs.push_back(Abbreviation("COOH", "OC(*)=O").onright("COOH", "CO2H").onleft("HOOC", "HO2C"));
      abbrs.push_back(Abbreviation("Ph", "*C1=CC=CC=C1").onright("Ph").onleft("Ph"));
      abbrs.push_back(Abbreviation("CF3", "FC(F)(F)*").onright("CF3").onleft("F3C"));
      abbrs.push_back(Abbreviation("ONO", "*ON=O").onright("ONO").onleft("ONO"));
      abbrs.push_back(Abbreviation("CN", "*C#N").onright("CN").onleft("NC"));
      abbrs.push_back(Abbreviation("NCO", "*N=C=O").onright("NCO").onleft("OCN"));
      abbrs.push_back(Abbreviation("OCH3", "CO[*]").onright("OCH3").onleft("OCH3"));
      abbrs.push_back(Abbreviation("SO3H", "OS(*)(=O)=O").onright("SO3H").onleft("HO3S"));
      abbrs.push_back(Abbreviation("SO2H", "OS(*)=O").onright("SO2H").onleft("HO2S"));
      abbrs.push_back(Abbreviation("PO3H2", "OP(O)(*)=O").onright("PO3H2").onleft("H2O3P"));
      abbrs.push_back(Abbreviation("ONO2", "*ON(=O)=O").onright("ONO2").onleft("O2NO"));
      abbrs.push_back(Abbreviation("OTMS", "C[Si](C)(C)O*").onright("OTMS").onleft("TMSO"));
      abbrs.push_back(Abbreviation("COOMe", "COC(*)=O").onright("COOMe").onleft("MeOOC"));
      abbrs.push_back(Abbreviation("BzO", "*OC(=O)C1=CC=CC=C1").onright("OBz").onleft("BzO"));
      abbrs.push_back(Abbreviation("AcO", "CC(=O)O*").onright("OAc").onleft("AcO"));
      abbrs.push_back(Abbreviation("NHBoc", "CC(C)(C)OC(=O)N*").onright("NHBoc").onleft("BocHN"));

      // This should not be [O-][N+](*)=O by request
      abbrs.push_back(Abbreviation("NO2", "*N(=O)=O").onright("NO2").onleft("O2N"));

      init = true;
   }

   string molString;
   ArrayOutput so(molString);
   MolfileSaver ma(so);
   ma.saveMolecule(molecule);
      
   indigoSetOption("treat-x-as-pseudoatom", "true");
   indigoSetOption("ignore-stereochemistry-errors", "true");

   int mol = indigoLoadMoleculeFromString(molString.c_str());
   //printf("***$%d\n", mol);

   if (mol == -1)
   {
      fprintf(stderr, "%s\n", indigoGetLastError());
      return molString;
   }

   int item, iter = indigoIterateAtoms(mol);
   //printf("***%d\n", iter);
      
   list<pair<int, int> > to_replace;
   vector<int> to_layout;

   while (item = indigoNext(iter))
   {
      //printf("$$$%d\n", item);
      if (item == -1)
         throw LogicException(indigoGetLastError());
   
      string symbol = indigoSymbol(item);
      bool found = false;
      for (size_t i = 0; i < abbrs.size() && !found; i++)
      {
         Abbreviation &cur = abbrs[i];
         BOOST_FOREACH(string label, cur.labels)
         {
            if (boost::iequals(symbol, label))               
            {
               to_replace.push_back(make_pair(item, i));
               found = true;
               break;
            }
         }
      }
      if (!found)
         indigoFree(item);
   }
   indigoFree(iter);

   if (to_replace.size() == 0)
      return molString;

   typedef pair<int, int> pair_i_i;
   BOOST_FOREACH(pair_i_i p, to_replace)
   {
      //printf("\t%s\n", p.second.c_str());
      const char *name = indigoSymbol(p.first);
      //printf("***%s\n", p.second.c_str());

      Abbreviation &abbr = abbrs[p.second];
      int expanded = indigoLoadMoleculeFromString(abbr.expansion.c_str());
      //printf("***%d\n", expanded);
         
      int attachment = 0;

      iter = indigoIterateAtoms(expanded);
      while (item = indigoNext(iter))
      {
         if (item == -1)
            throw LogicException(indigoGetLastError());
            
         if (indigoIsRSite(item))
         {
            int item2, iter2 = indigoIterateNeighbors(item);
            while (item2 = indigoNext(iter2))
            {
               if (item2 == -1)
                  throw LogicException(indigoGetLastError());
   
               attachment = item2;
                  
               //Only 1 attachment point. So, no freeing here
               //indigoFree(item2);
            }      
            indigoFree(iter2);
               
            indigoRemove(item);
            break;
         }
         indigoFree(item);          
      }
      indigoFree(iter);
         
      int item2, iter2 = indigoIterateNeighbors(p.first);
      int atom_from, bond_order;
      while (item2 = indigoNext(iter2))
      {
         if (item2 == -1)
            throw LogicException(indigoGetLastError());         

         atom_from = item2;
         bond_order = indigoBondOrder(indigoBond(atom_from));
      }
      indigoFree(iter2);
         
      //printf("***%d\n", bond_order);
         
      float xyz[3];
      memcpy(xyz, indigoXYZ(p.first), 3 * sizeof(float));
      indigoRemove(p.first);
       
      int mapping = indigoMerge(mol, expanded);
      int mapped = indigoMapAtom(mapping, attachment);

      indigoAddBond(atom_from, mapped, bond_order);
      indigoSetXYZ(mapped, xyz[0], xyz[1], xyz[2]);
         
      vector<int> superatom_vertices;
      iter = indigoIterateAtoms(expanded);
      while (item = indigoNext(iter))
      {
         if (item == -1)
            throw LogicException(indigoGetLastError());         
            
         int midx = indigoIndex(indigoMapAtom(mapping, item));
         superatom_vertices.push_back(midx);
            
         int attach_index = indigoIndex(attachment);
         if (indigoIndex(item) != attach_index)
         {
            to_layout.push_back(midx);
         }
      }
      indigoFree(iter);
         
      indigoAddSuperatom(mol, superatom_vertices.size(), &superatom_vertices[0], abbr.name.c_str());
      //indigoFree(attachment);
      //indigoFree(atom_from);
      //indigoFree(mapped);
      //indigoFree(mapping);
   }
      
   int subm = indigoGetSubmolecule(mol, to_layout.size(), &to_layout[0]);
   indigoLayout(subm);
      
   string newMolfile = indigoMolfile(mol);
   //puts(newMolfile.c_str());
   //indigoFree(subm);
   //indigoFree(mol);
   return newMolfile;
}

}
