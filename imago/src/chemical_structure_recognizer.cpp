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
#include "prefilter_cv.h"
#include "prefilter.h" // line thickness estimation
#include "pixel_boundings.h"
#include "weak_segmentator.h"
#include "platform_tools.h"

using namespace imago;

ChemicalStructureRecognizer::ChemicalStructureRecognizer() : _cr(3) // TODO
{
}

ChemicalStructureRecognizer::ChemicalStructureRecognizer( const char *fontname )
   : _cr(3, fontname)
{
}

void ChemicalStructureRecognizer::recognize(Settings& vars, Molecule &mol) 
{
	logEnterFunction();

   try
   {
      mol.clear();

      SegmentDeque layer_symbols, layer_graphics, segments;
      
      Image &_img = _origImage;

      _img.crop();
	  vars.general.ImageWidth = _img.getWidth();
	  vars.general.ImageHeight = _img.getHeight();

      if (!_img.isInit())
      {
		  throw ImagoException("Empty image, nothing to recognize");
      }

	  vars.estimation.LineThickness = estimateLineThickness(_img, vars.routines.LineThick_Grid);
	  
	  getLogExt().appendImage("Cropped image", _img);

	  // extract segments using WeakSegmentator
	  WeakSegmentator ws(_img.getWidth(), _img.getHeight());
	  // ws.ConnectMode = true;
	  ws.appendData(prefilter_cv::ImgAdapter(_img, _img), vars.csr.WeakSegmentatorDist);
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
	  // ------------------------

      if (segments.size() == 0)
      {
         throw ImagoException("Empty image, nothing to recognize");
      }

      WedgeBondExtractor wbe(segments, _img);
      {
         int sdb_count = wbe.singleDownFetch(vars, mol);
		 getLogExt().append("Single-down bonds found", sdb_count);
      }
	  
      Separator sep(segments, _img);

      sep.firstSeparation(vars, layer_symbols, layer_graphics);

	  getLogExt().append("Symbols", layer_symbols.size());
	  getLogExt().append("Graphics", layer_graphics.size());

	  if (layer_graphics.size() == 0 && layer_symbols.size() == 1)
	  {
		  getLogExt().appendText("HACK: No graphics detected, assume symbols are graphics");
		  layer_graphics = layer_symbols;
		  layer_symbols.clear();
	  }

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

	  if (vars.general.ExtractCharactersOnly)
	  {
		  BOOST_FOREACH( Segment *s, layer_symbols )
		  {
			  RecognitionDistance rd = getCharacterRecognizer().recognize_all(vars, *s, CharacterRecognizer::all, true);
			  double dist = 0.0;
			  char res = rd.getBest(&dist);
			  double qual = rd.getQuality();

			  char filename[MAX_TEXT_LINE] = {0};

			  platform::MKDIR("./characters");

			  if (dist > vars.characters.PossibleCharacterDistanceWeak)
			  {
				  platform::MKDIR("./characters/bad");
				  sprintf(filename, "./characters/bad/%c_d%4.2f_q%4.2f.png", res, dist, qual);
			  }
			  else if (qual < vars.characters.PossibleCharacterMinimalQuality)
			  {
				  platform::MKDIR("./characters/similar");
				  sprintf(filename, "./characters/similar/%c_d%4.2f_q%4.2f.png", res, dist, qual);
			  }
			  else
			  {
				  platform::MKDIR("./characters/good");
				  sprintf(filename, "./characters/good/%c_d%4.2f_q%4.2f.png", res, dist, qual);
			  }

			  ImageUtils::saveImageToFile(*s, filename);
		  }
		  return;
	  }


      if (!layer_symbols.empty())
      {
         LabelCombiner lc(vars, layer_symbols, layer_graphics, _cr);

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
		gd.extractRingsCenters(vars, layer_graphics, ringCenters);
		GraphExtractor::extract(vars, gd, layer_graphics, mol);
	}
	else
	{
		double lnThickness = vars.estimation.LineThickness;
		getLogExt().append("Line Thickness", lnThickness);
		CvApproximator cvApprox;
		GraphicsDetector gd(&cvApprox, lnThickness * vars.csr.LineVectorizationFactor);
		gd.extractRingsCenters(vars, layer_graphics, ringCenters);
		GraphExtractor::extract(vars, gd, layer_graphics, mol);
	}		  

      wbe.singleUpFetch(vars, mol);

	  while (mol._dissolveShortEdges(vars.csr.Dissolve, true));

	  mol.deleteBadTriangles(vars.csr.DeleteBadTriangles);
      
      if (!layer_symbols.empty())
      {         
		 LabelLogic ll(_cr);
         std::deque<Label> unmapped_labels;
                 
         BOOST_FOREACH(Label &l, mol.getLabels())
            ll.recognizeLabel(vars, l);
         
		 getLogExt().appendText("Label recognizing");
         
         mol.mapLabels(vars, unmapped_labels);

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

void ChemicalStructureRecognizer::image2mol(Settings& vars, Image &img, Molecule &mol )
{
	logEnterFunction();
	setImage(img);
	recognize(vars, mol);
}

void ChemicalStructureRecognizer::extractCharacters(Settings& vars, Image &img )
{
	logEnterFunction();
	setImage(img);
	Molecule temp;
	// force-set characters extraction only:
	vars.general.ExtractCharactersOnly = true;
	recognize(vars, temp);
}

void ChemicalStructureRecognizer::setImage( Image &img )
{
   _origImage.copy(img);
}

ChemicalStructureRecognizer::~ChemicalStructureRecognizer()
{
}
