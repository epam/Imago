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

#include <boost/foreach.hpp>

#include "binarizer.h"
#include "chemical_structure_recognizer.h"
#include "graph_extractor.h"
#include "graphics_detector.h"
#include "image.h"
#include "image_utils.h"
#include "image_draw_utils.h"
#include "label_combiner.h"
#include "label_logic.h"
#include "molecule.h"
#include "segment.h"
#include "segmentator.h"
#include "separator.h"
#include "superatom.h"
#include "thin_filter2.h"
#include "vec2d.h"
#include "wedge_bond_extractor.h"
#include "log_ext.h"
#include "label_logic.h"
#include "approximator.h"
#include "prefilter.h"
#include "prefilter_cv.h"
#include "pixel_boundings.h"
#include "weak_segmentator.h"
#include "constants.h"

using namespace imago;

ChemicalStructureRecognizer::ChemicalStructureRecognizer() : _cr(3)
{
}

ChemicalStructureRecognizer::ChemicalStructureRecognizer( const char *fontname )
   : _cr(3, fontname)
{
}


void ChemicalStructureRecognizer::extractCharacters( Image &img )
{
	logEnterFunction();
	setImage(img);
	Molecule temp;
	recognize(temp, true);
}

void ChemicalStructureRecognizer::recognize( Molecule &mol, bool only_extract_characters ) 
{
	logEnterFunction();

   try
   {
      mol.clear();

      SegmentDeque layer_symbols, layer_graphics, segments;
      
      Image &_img = _origImage;

	  vars.general.OriginalImageWidth = _img.getWidth();
	  vars.general.OriginalImageHeight = _img.getHeight();

      _img.crop();

      if (!_img.isInit())
      {
         throw ImagoException("Empty image, nothing to recognize");
      }

	  vars.general.ImageWidth = _img.getWidth();
	  vars.general.ImageHeight = _img.getHeight();
	  vars.update();

	  vars.estimation.LineThickness = estimateLineThickness(_img);
	  
	  getLogExt().appendImage("Cropped image", _img);

	  ////////////-----------------------
	  WeakSegmentator ws(_img.getWidth(), _img.getHeight());
	  //ws.ConnectMode = true;
	  ws.appendData(ImgAdapter(_img, _img), vars.csr.WeakSegmentatorDist);
	  for (WeakSegmentator::SegMap::iterator it = ws.SegmentPoints.begin(); it != ws.SegmentPoints.end(); it++)
	  {
		  const Points2i& pts = it->second;
		  RectShapedBounding b(pts);
		  Segment *s = new Segment();
		  s->init(b.getBounding().width+1, b.getBounding().height+1);
		  s->fillWhite();
		  s->getX() = b.getBounding().x;
		  s->getY() = b.getBounding().y;
		  for (size_t u = 0; u < pts.size(); u++)
			s->getByte(pts[u].x - b.getBounding().x, pts[u].y - b.getBounding().y) = 0;
		  segments.push_back(s);
	  }
	  ///////////------------------------

      if (segments.size() == 0)
      {
         throw ImagoException("Empty image, nothing to recognize");
      }

      WedgeBondExtractor wbe(segments, _img);
      {
         int sdb_count = wbe.singleDownFetch(mol);
		 getLogExt().append("Single-down bonds found", sdb_count);
      }
	  
      Separator sep(segments, _img);

      sep.firstSeparation(layer_symbols, layer_graphics);

	  getLogExt().append("Symbols", layer_symbols.size());
	  getLogExt().append("Graphics", layer_graphics.size());
      
	  if (getLogExt().loggingEnabled())
      {
         Image symbols, graphics;

         symbols.emptyCopy(_img);
         graphics.emptyCopy(_img);

         BOOST_FOREACH( Segment *s, layer_symbols )
            ImageUtils::putSegment(symbols, *s, true);

         BOOST_FOREACH( Segment *s, layer_graphics )
            ImageUtils::putSegment(graphics, *s, true);

		 getLogExt().appendImage("Letters", symbols);
		 getLogExt().appendImage("Graphics", graphics);
      }

	  if (only_extract_characters)
	  {
		  BOOST_FOREACH( Segment *s, layer_symbols )
		  {
			  RecognitionDistance rd = getCharacterRecognizer().recognize_all(*s, CharacterRecognizer::all, false);
			  double dist = 0.0;
			  char res = rd.getBest(&dist);
			  double qual = rd.getQuality();

			  char filename[1024] = {0};

			  if (dist > vars.characters.PossibleCharacterDistanceWeak)
			  {
				  sprintf(filename, "./characters/bad/%c_d%f_q%f.png", res, dist, qual);
			  }
			  else if (qual < vars.characters.PossibleCharacterMinimalQuality)
			  {
				  sprintf(filename, "./characters/similar/%c_d%f_q%f.png", res, dist, qual);
			  }
			  else
			  {
				  sprintf(filename, "./characters/good/%c_d%f_q%f.png", res, dist, qual);
			  }

			  ImageUtils::saveImageToFile(*s, filename);
		  }
		  return;
	  }


      if (!layer_symbols.empty())
      {
         LabelCombiner lc(layer_symbols, layer_graphics, _cr);

		 if (vars.estimation.CapitalHeight > 0.0)
            lc.extractLabels(mol.getLabels());

		 if (getLogExt().loggingEnabled())
         {
            Image symbols;
            symbols.emptyCopy(_img);
            BOOST_FOREACH( Segment *s, layer_symbols )
               ImageUtils::putSegment(symbols, *s, true);
            getLogExt().appendImage("Symbols with layer_symbols added", symbols);
         }

		 getLogExt().append("Found superatoms", mol.getLabels().size());
      }
      else
      {
		  getLogExt().appendText("No symbols found");
      }

      Points2d ringCenters;

	getLogExt().appendText("Before line vectorization");

	if (vars.csr.UseSimpleApproximator)
	{
		SimpleApproximator sApprox;
		GraphicsDetector gd(&sApprox, 0.3); // no one cares
		gd.extractRingsCenters(layer_graphics, ringCenters);
		GraphExtractor::extract(gd, layer_graphics, mol);
	}
	else
	{
		double lnThickness = vars.estimation.LineThickness;
		getLogExt().append("Line Thickness", lnThickness);
		CvApproximator cvApprox;
		GraphicsDetector gd(&cvApprox, lnThickness * vars.csr.LineVectorizationFactor);
		gd.extractRingsCenters(layer_graphics, ringCenters);
		GraphExtractor::extract(gd, layer_graphics, mol);
	}		  

      wbe.singleUpFetch(mol);

	  while (mol._dissolveShortEdges(vars.csr.Dissolve, true));

	  mol.deleteBadTriangles(vars.csr.DeleteBadTriangles);
      
      if (!layer_symbols.empty())
      {         
		 LabelLogic ll(_cr);
         std::deque<Label> unmapped_labels;
                 
         BOOST_FOREACH(Label &l, mol.getLabels())
            ll.recognizeLabel(l);
         
		 getLogExt().appendText("Label recognizing");
         
         mol.mapLabels(unmapped_labels);

         GraphicsDetector().analyzeUnmappedLabels(unmapped_labels, ringCenters);
		 getLogExt().append("Found rings", ringCenters.size());
      }
	  else
	  {
		  getLogExt().appendText("Layer_symbols is empty!");
	  }

      mol.aromatize(ringCenters);
	  //mol._connectBridgedBonds();

      wbe.fixStereoCenters(mol);      

      BOOST_FOREACH( Segment *s, layer_symbols )
         delete s;
      BOOST_FOREACH( Segment *s, layer_graphics )
         delete s;

      layer_symbols.clear();
      layer_graphics.clear();

	  getLogExt().appendText("Recognition finished");
   }
   catch (ImagoException&)
   {
      throw;
   }

}

void ChemicalStructureRecognizer::image2mol( Image &img, Molecule &mol )
{
	logEnterFunction();
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
