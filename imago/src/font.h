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

#ifndef _font_h
#define _font_h

#include "symbol_features.h"
#include "character_recognizer_data.h"
#include "stl_fwd.h"
#include <string>

namespace imago
{
   class Image;
   class Segment;

   class Font : FontRecognizerData
   {
   public:

      enum BUILT_IN_FONTS
      {
         ARIAL = 0,
         ARIAL_BOLD,
         SERIF,
         MAX_FONTS
      };

      Font( const char *filename, int descCount );
      Font( int font_id );

      ~Font();

      char findBest( const SymbolFeatures &features, int begin, int end,
                     double *dist = 0 ) const;

      char findBest( const Segment *img, int begin, int end,
                     double *dist = 0 ) const;

      char findBest( const Segment *img, const std::string &letters,
                     double *dist = 0 ) const;

      int findCapitalHeight( SegmentDeque &segments ) const;
   public:
      Font(const Font& other);
      
      double _compare( int ind, const SymbolFeatures &features ) const;
      static double _compareDescriptors( const std::vector<double> &d1,
                                         const std::vector<double> &d2 );
      void _loadFromImage( const char *imgname );
      void _loadFromFile( const char *filename );

      void _loadArial();
      void _loadArialBold();
      void _loadSerif();
   };
}


#endif	/* _font_h */

