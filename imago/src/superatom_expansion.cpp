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
   int degree;

   Abbreviation (const std::string &name, const std::string &expansion) : name(name), expansion(expansion)
   {
      degree = std::count(expansion.begin(), expansion.end(), '*');
   }

   Abbreviation& add(const std::string &label)
   {
      labels.push_back(label);
      return *this;
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

std::string expandSuperatoms(const Settings& vars, const Molecule &molecule )
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
      abbrs.push_back(Abbreviation("OCH3", "CO[*]").onright("OCH3").onleft("H3CO"));

	   abbrs.push_back(Abbreviation("COOCH3", "COC([*])=O").onright("COOCH3"));
	   abbrs.push_back(Abbreviation("SO2", "[*:2]OS([*:1])=O").add("SO2"));
	   abbrs.push_back(Abbreviation("CH2CH", "[*:1]CC([*:2])[*:3]").add("CH2CH"));
	   abbrs.push_back(Abbreviation("OCH", "[*:1]OC([*:2])[*:3]").add("OCH"));
	   abbrs.push_back(Abbreviation("CO", "[*:1]C([*:2])=O").add("CO"));

      abbrs.push_back(Abbreviation("SO3H", "OS(*)(=O)=O").onright("SO3H").onleft("HO3S"));
      abbrs.push_back(Abbreviation("SO2H", "OS(*)=O").onright("SO2H").onleft("HO2S"));
      abbrs.push_back(Abbreviation("PO3H2", "OP(O)(*)=O").onright("PO3H2").onleft("H2O3P"));
      abbrs.push_back(Abbreviation("ONO2", "*ON(=O)=O").onright("ONO2").onleft("O2NO"));
      abbrs.push_back(Abbreviation("OTMS", "C[Si](C)(C)O*").onright("OTMS").onleft("TMSO"));
      abbrs.push_back(Abbreviation("COOMe", "COC(*)=O").onright("COOMe").onleft("MeOOC"));
      abbrs.push_back(Abbreviation("BzO", "*OC(=O)C1=CC=CC=C1").onright("OBz").onleft("BzO"));
      abbrs.push_back(Abbreviation("AcO", "CC(=O)O*").onright("OAc").onleft("AcO"));
      abbrs.push_back(Abbreviation("NHBoc", "CC(C)(C)OC(=O)N*").onright("NHBoc").onleft("BocHN"));

      abbrs.push_back(Abbreviation("CHO", "*C=O").onright("CHO").onleft("OCH"));

      // This should not be [O-][N+](*)=O by request
      abbrs.push_back(Abbreviation("NO2", "*N(=O)=O").onright("NO2").onleft("O2N"));	  

      // Two-sided abbreviations
      abbrs.push_back(Abbreviation("COOCH2", "[*:1]C(=O)OC[*:2]").add("COOCH2"));	  


      init = true;
   }

   string molString;
   ArrayOutput so(molString);
   MolfileSaver ma(so);
   ma.saveMolecule(vars, molecule);
      
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
      int degree = indigoDegree(item);
      int abbr_idx = -1;
      for (size_t i = 0; i < abbrs.size(); i++)
      {
         Abbreviation &cur = abbrs[i];
         if (degree > cur.degree)
            continue;

         BOOST_FOREACH(string label, cur.labels)
         {
            if (boost::iequals(symbol, label))               
            {
               // Distinguish between same abbreviations with different degree
               if (abbr_idx != -1 && cur.degree > abbrs[abbr_idx].degree)
                  continue;
               abbr_idx = i;
               break;
            }
         }
      }
      if (abbr_idx != -1)
         to_replace.push_back(make_pair(item, abbr_idx));
      else
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
         
      const int NEI_COUNT = 3;
      int attachment[NEI_COUNT] = {-1};

      iter = indigoIterateAtoms(expanded);
      while (item = indigoNext(iter))
      {
         if (item == -1)
            throw LogicException(indigoGetLastError());
            
         if (indigoIsRSite(item))
         {
            int rsite_group = indigoSingleAllowedRGroup(item);
            if (rsite_group == -1)
               rsite_group = 1;

            int item2, iter2 = indigoIterateNeighbors(item);
            while (item2 = indigoNext(iter2))
            {
               if (item2 == -1)
                  throw LogicException(indigoGetLastError());
   
               if (rsite_group >= NEI_COUNT + 1)
                  throw LogicException("Invalid abbreviation expansion");
               attachment[rsite_group - 1] = item2;
            }      
            indigoFree(iter2);
               
            indigoRemove(item);
         }
         else
            indigoFree(item);          
      }
      indigoFree(iter);
      
      float xyz[3];
      memcpy(xyz, indigoXYZ(p.first), 3 * sizeof(float));

      int item2, iter2 = indigoIterateNeighbors(p.first);
      struct neiAtom
      {
         int atom;
         int bond_order;
         float angle;
         Vec2f dir;

         static bool less (neiAtom &a1, neiAtom &a2)
         {
            return a1.angle < a2.angle;
         }
      };
      neiAtom attachment_atoms[NEI_COUNT];
      int attachment_atoms_count = 0;

      bool invalid_atom = false;
      while (item2 = indigoNext(iter2))
      {
         if (item2 == -1)
            throw LogicException(indigoGetLastError());         

         int bond = indigoBond(item2);

         if (attachment_atoms_count >= NEI_COUNT)
         {
            fprintf(stderr, "Abbreviation has too many connections");
            invalid_atom = true;
            break;
         }
         neiAtom &cur_atom = attachment_atoms[attachment_atoms_count];
         cur_atom.atom = item2;
         cur_atom.bond_order = indigoBondOrder(bond);
         float nei_xyz[3];
         memcpy(nei_xyz, indigoXYZ(item2), 3 * sizeof(float));
         cur_atom.dir.x = nei_xyz[0] - xyz[0];
         cur_atom.dir.y = nei_xyz[1] - xyz[1];
         attachment_atoms_count++;                 

         indigoFree(bond);
      }
      indigoFree(iter2);

      if (invalid_atom)
         continue;
      
      // Find left most attachement
      int left_most = 0;
      for (int i = 1; i < attachment_atoms_count; i++)
         if (attachment_atoms[i].dir.x < attachment_atoms[left_most].dir.x)
            left_most = i;
      for (int i = 0; i < attachment_atoms_count; i++)
      {
         Vec2f v1(attachment_atoms[i].dir.x, attachment_atoms[i].dir.y);
         Vec2f v2(attachment_atoms[left_most].dir.x, attachment_atoms[left_most].dir.y);

         attachment_atoms[i].angle = Vec2f::angle(v1, v2);
      }

      // Sort attachment points according to the angle
      std::sort(attachment_atoms, attachment_atoms + attachment_atoms_count, neiAtom::less); 

      //printf("***%d\n", bond_order);
         
      indigoRemove(p.first);
       
      int mapping = indigoMerge(mol, expanded);

      for (int att_idx = 0; att_idx < attachment_atoms_count; att_idx++)
      {
         neiAtom &cur_att = attachment_atoms[att_idx];
         if (attachment[att_idx] == -1)
         {
            fprintf(stderr, "There is no connection to the abbreviation");
            continue;
         }
         int mapped = indigoMapAtom(mapping, attachment[att_idx]);

         indigoAddBond(cur_att.atom, mapped, cur_att.bond_order);
         indigoSetXYZ(mapped, xyz[0], xyz[1], xyz[2]);
      }
         
      vector<int> superatom_vertices;
      iter = indigoIterateAtoms(expanded);
      while (item = indigoNext(iter))
      {
         if (item == -1)
            throw LogicException(indigoGetLastError());         
            
         int midx = indigoIndex(indigoMapAtom(mapping, item));
         superatom_vertices.push_back(midx);
            
         int attach_index = indigoIndex(attachment[0]);
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
