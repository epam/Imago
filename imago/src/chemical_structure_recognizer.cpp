/****************************************************************************
 * Copyright (C) 2009-2010 GGA Software Services LLC
 * 
 * This file is part of Imago toolkit.
 * 
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

#include <cstdio>
#include <cmath>
#include <memory>
#include <deque>

#include "boost/foreach.hpp"

#include "binarizer.h"
#include "chemical_structure_recognizer.h"
#include "convolver.h"
#include "font.h"
#include "graph_extractor.h"
#include "graphics_detector.h"
#include "image.h"
#include "image_utils.h"
#include "image_draw_utils.h"
#include "label_combiner.h"
#include "label_logic.h"
#include "log.h"
#include "molecule.h"
#include "recognition_settings.h"
#include "segment.h"
#include "segmentator.h"
#include "separator.h"
#include "superatom.h"
#include "thin_filter2.h"
#include "thread_local_ptr.h"
#include "vec2d.h"
#include "wedge_bond_extractor.h"
#include "current_session.h"
#include "label_logic.h"

using namespace imago;

ChemicalStructureRecognizer::ChemicalStructureRecognizer() : _cr(3)
{
}

ChemicalStructureRecognizer::ChemicalStructureRecognizer( const char *fontname )
   : _cr(3, fontname)
{
}

// void ChemicalStructureRecognizer::_selectFont( const SegmentDeque &layer )
// {
//    boost::shared_ptr<Font> serif(new Font(Font::SERIF));
//    boost::shared_ptr<Font> arial(new Font(Font::ARIAL));

//    double dist_a = 0, dist_s = 0;
//    double tmp;

//    for (SegmentDeque::const_iterator it = layer.begin();
//         it != layer.end(); ++it)
//    {
//       double w = (*it)->getWidth();
//       double h = (*it)->getHeight();

//       if (w / h > 1.15) //"Constants"
//          continue;

//       serif->findBest(*it, 0, 26, &tmp); //"Constants"
//       dist_s += tmp;

//       arial->findBest(*it, 0, 26, &tmp); //"Constants"
//       dist_a += tmp;
//    }
//    if (dist_a < dist_s)
//    {
//       _fnt = arial;
//    }
//    else
//    {
//       _fnt = serif;
//    }
// }

void ChemicalStructureRecognizer::_processFilter()
{
   RecognitionSettings &rs = getSettings();

   const char *str = rs["Filter"];

   if (strcmp(str, "blur") == 0)
   {
      Convolver conv(_origImage);

      conv.initGauss();
      conv.apply();
   }
   if (strcmp(str, "sharp") == 0)
   {
      Convolver conv(_origImage);

      conv.initSharp();
      conv.apply();
   }

   //TODO: Check threshold
   Binarizer(_origImage, rs["BinarizationLvl"]).apply();
}

void ChemicalStructureRecognizer::recognize( Molecule &mol ) 
{
   try
   {
      getLog().reset();
      mol.clear();

      SegmentDeque layer_symbols, layer_graphics, segments;
      RecognitionSettings &rs = getSettings();      
      
      LMARK;
      LPRINT(0 , "Let the recognition begin");

      TIME(_processFilter(), "Image processing");

      //Notice, that there is no supersegmentation procedure
      Image &_img = _origImage;

      rs.set("imgHeight", _img.getHeight());
      rs.set("imgWidth", _img.getWidth());

      if (rs["DebugSession"])
      {
         ImageUtils::saveImageToFile(_img, "output/real_img.png");
      }

      TIME(Segmentator::segmentate(_img, segments), "Normal segmentation");

      WedgeBondExtractor wbe(segments, _img); 
      TIME(wbe.singleDownFetch(mol), "Fetching single-down bonds");

      Separator sep(segments, _img);

      //Settings for handwriting separation
      rs.set("SymHeightErr", 42);      
      rs.set("MaxSymRatio", 1.4);      

      TIME(sep.firstSeparation(layer_symbols, layer_graphics), 
         "Symbols/Graphics elements separation");
      LPRINT(0, "Symbols: %i, Graphics: %i", layer_symbols.size(), 
         layer_graphics.size());

      if (rs["DebugSession"])
      {
         Image symbols, graphics;

         symbols.emptyCopy(_img);
         graphics.emptyCopy(_img);

         BOOST_FOREACH( Segment *s, layer_symbols )
            ImageUtils::putSegment(symbols, *s, true);

         BOOST_FOREACH( Segment *s, layer_graphics )
            ImageUtils::putSegment(graphics, *s, true);

         ImageUtils::saveImageToFile(symbols, "output/letters.png");
         ImageUtils::saveImageToFile(graphics, "output/graphics.png");
      }

      LMARK;
      if (!layer_symbols.empty())
      {
         LabelCombiner lc(layer_symbols, layer_graphics,
                          rs["CapitalHeight"], _cr);
         lc.extractLabels(mol.getLabels());

         if (rs["DebugSession"])
         {
            Image symbols;
            symbols.emptyCopy(_img);
            BOOST_FOREACH( Segment *s, layer_symbols )
               ImageUtils::putSegment(symbols, *s, true);
            ImageUtils::saveImageToFile(symbols, "output/letters2.png");
         }

         LPRINT(1, "Found %d superatoms", mol.getLabels().size());
      }
      else
      {
         LPRINT(1, "No symbols found in image");
      }

      Points ringCenters;

      TIME(GraphicsDetector().extractRingsCenters(layer_graphics, ringCenters), 
         "Extracting aromatic rings");

      

      TIME(GraphExtractor::extract(layer_graphics, mol), 
         "Extracting molecular graph");

      //TIME(wbe.singleUpFetch(mol), "Fetching single-up bonds");

      if (!layer_symbols.empty())
      {
         LMARK;
         LabelLogic ll(_cr, getSettings()["CapHeightErr"]);
         std::deque<Label> unmapped_labels;
         BOOST_FOREACH(Label &l, mol.getLabels())
            ll.recognizeLabel(l);

         LPRINT(1, "Label recognizing");
         
         mol.mapLabels(unmapped_labels);

         GraphicsDetector().analyzeUnmappedLabels(unmapped_labels, ringCenters);
         LPRINT(0, "Found %i rings", ringCenters.size());
      }

      mol.aromatize(ringCenters);

      TIME(wbe.fixStereoCenters(mol), "Fixing stereo bonds directions");

      LPRINT(0, "Compound recognized with #%i config", (int)rs["CfgNumber"] + 1);

      BOOST_FOREACH( Segment *s, layer_symbols )
         delete s;
      BOOST_FOREACH( Segment *s, layer_graphics )
         delete s;

      LPRINT(1, "Recognition finished");
   }
   catch (Exception &e)
   {
      throw NoResultException("caused by: %s", e.what());
   }
}

void ChemicalStructureRecognizer::image2mol( Image &img, Molecule &mol )
{
   setImage(img);
   recognize(mol);
}

void ChemicalStructureRecognizer::setImage( Image &img )
{
   _origImage.copy(img);
}

ChemicalStructureRecognizer::~ChemicalStructureRecognizer()
{
}
