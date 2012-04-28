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

#include <cmath>
#include <cstdarg>
#include <algorithm>
#include <string>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "image.h"
#include "image_utils.h"
#include "image_draw_utils.h"
#include "output.h"
#include "scanner.h"
#include "segment.h"
#include "thin_filter2.h"
#include "vec2d.h"
#include "log_ext.h"
#include "constants.h"

namespace imago
{
   bool ImageUtils::testVertHorLine( Segment &img, int &angle )
   {
      Image tmp;

      tmp.copy(img);
      ThinFilter2(tmp).apply();
      tmp.crop();

      int w = tmp.getWidth(), h = tmp.getHeight();

      if (w < 2 && w < h)
      {
         angle = -1;
         return true;
      }

      if (h < 2 && h < w)
      {
         angle = 1;
         return true;
      }

      angle = 0;

      return false;
   }

   bool ImageUtils::testSlashLine( Segment &img, double *angle, double eps )
   {
      double density, thetha, r;

      //ImageUtils::saveImageToFile(img, "output/origin.png");

      Image tmp;   

      tmp.copy(img);   
      ThinFilter2(tmp).apply();   
   
      thetha = PI_2 + atan2((double)img.getHeight(), (double)img.getWidth());
      r = 0;
      density = tmp.density();
      ImageDrawUtils::putLine(tmp, thetha, r, eps, 255);
      density = tmp.density() / density;
      //ImageUtils::saveImageToFile(tmp, "output/origin_orient1.png");

	  if (density < consts::ImageUtils::SlashLineDensity)
      {
         if (angle != 0)
            *angle = thetha;
         return true;
      }

      tmp.copy(img);
      ThinFilter2(tmp).apply();   

      thetha = -thetha;
      r = cos(thetha) * img.getWidth();
      density = tmp.density();
      ImageDrawUtils::putLine(tmp, thetha, r, eps, 255);
      density = tmp.density() / density;
      //ImageUtils::saveImageToFile(tmp, "output/origin_orient2.png");
   
      if (density < consts::ImageUtils::SlashLineDensity)
      {
         if (angle != 0)
            *angle = thetha;
         return true;
      }

      if (angle != 0)
         *angle = thetha;

      return false;
   }

   int ImageUtils::findCornerRect( const Segment &img, bool corner, bool side,
                                   bool orient, int &out_w, int &out_h )
   {
      //
      int x, y, w, h, dy, dx;
      int max_sq = 0;

      if (!corner)
         y = 0, dy = 1;
      else
         y = img.getHeight() - 1, dy = -1;

      if (!side)
         x = 0, dx = 1;
      else
         x = img.getWidth() - 1, dx = -1;

      int lim_y = (dy > 0) ? img.getHeight() : 0;
      int lim_x = (dx > 0) ? img.getWidth() : 0;


      out_w = out_h = 0;
      for (h = 1; y != lim_y; y += dy, h++)
      {
         if (img.getByte(0, y) != 255)
            break;
         for (w = 1; x != lim_x; x += dx, w++)
         {
            if (img.getByte(x, y) != 255)
            {
               if (!side)
                  lim_x = std::min(x, lim_x);
               else
                  lim_x = std::max(x, lim_x);
            
               break;
            }

            if (!orient && w > h)
               break;

            if (orient && h > w)
               continue;

            if (w * h > max_sq)
            {
               max_sq = w * h;
               out_w = w;
               out_h = h;
            }
         }

         if (!side)
            x = 0;
         else
            x = img.getWidth() - 1;
      }
      return max_sq;
   }

   bool ImageUtils::testPlus( const Segment &img )
   {
      int sq[4];
      int w[4], h[4];
      int sum = 0;
      int s = img.getWidth() * img.getHeight();

      sq[0] = ImageUtils::findCornerRect(img, 0, 0, 0, w[0], h[0]);
      sq[1] = ImageUtils::findCornerRect(img, 0, 1, 0, w[1], h[1]);
      sq[2] = ImageUtils::findCornerRect(img, 1, 0, 0, w[2], h[2]);
      sq[3] = ImageUtils::findCornerRect(img, 1, 1, 0, w[3], h[3]);

      sum = sq[0] + sq[1] + sq[2] + sq[3];

      int max_sq = *std::max_element(sq, sq + 4);

      double density = (double)sum / s;

	  if (density > consts::ImageUtils::TestPlusDensity)
   {
	   getLogExt().append("[testPlus] Density", density);     
   }

      //TODO: write more convenient criteria
      return (density > consts::ImageUtils::TestPlusDensity 
		      && max_sq < consts::ImageUtils::TestPlusSq * s);  // 0.55
   }

   bool ImageUtils::testMinus( const Segment &img, int cap_height )
   {
      int w = img.getWidth(), h = img.getHeight();
      int black = 0;
      int total = w * h;
      for (int i = 0; i < total; i++)
      {
         if (img[i] == 0)
            black++;
      }

      double density = (double)black / total;
      double ratio = (double)h / w;

	  return (ratio < consts::ImageUtils::TestMinusRatio 
		  && density > consts::ImageUtils::TestMinusDensity 
		  && w < consts::ImageUtils::TestMinusHeightFactor * cap_height); 
   }

   void ImageUtils::putSegment( Image &img, const Segment &seg, bool careful )
   {
      int i, j, img_cols = img.getWidth(),
         seg_x = seg.getX(), seg_y = seg.getY(),
         seg_rows = seg.getHeight(), seg_cols = seg.getWidth(),
         img_size = img.getWidth() * img.getHeight();

      for (j = 0; j < seg_rows; j++)
         for (i = 0; i < seg_cols; i++)
         {
            int address = (j + seg_y) * img_cols + (i + seg_x);

            if (address < img_size)
            { 
               if (careful)
               {
                  if (img[address] == 255)
                     img[address] = seg.getByte(i, j);
               }
               else
                  img[address] = seg.getByte(i, j);
            }
         }
   }

   void ImageUtils::cutSegment( Image &img, const Segment &seg, bool forceCut, byte val )
   {
      int i, j, img_cols = img.getWidth(),
         seg_x = seg.getX(), seg_y = seg.getY(),
         seg_rows = seg.getHeight(), seg_cols = seg.getWidth();

      for (j = 0; j < seg_rows; j++)
         for (i = 0; i < seg_cols; i++)
         {
            int address = (j + seg_y) * img_cols + (i + seg_x);

            if (seg.getByte(i, j) == 0)
               if (img[address] == 0 || forceCut)
                  img[address] = val;
         }
   }

   void ImageUtils::copyImageToMat ( const Image &img, cv::Mat &mat)
   {
      int w = img.getWidth();
      int h = img.getHeight();

      mat.create(h, w, CV_8U);
      int i, j;

      for (i = 0; i < w; i++)
         for (j = 0; j < h; j++)
            mat.at<unsigned char>(j, i) = img.getByte(i, j);
   }

   void ImageUtils::copyMatToImage (const cv::Mat &mat, Image &img)
   {
      int w = mat.cols;
      int h = mat.rows;

      img.init(w, h);
      int i, j;

      for (i = 0; i < w; i++)
         for (j = 0; j < h; j++)
            img.getByte(i, j) = mat.at<unsigned char>(j, i);
   }

   void ImageUtils::loadImageFromBuffer( const std::vector<byte> &buffer, Image &img )
   {
      cv::Mat mat = cv::imdecode(cv::Mat(buffer), 0);
      if (mat.empty())
         throw Exception("Image data is invalid");
      copyMatToImage(mat, img);
   }

   void ImageUtils::loadImageFromFile( Image &img, const char *format, ... )
   {
      char str[MAX_LINE];
      va_list args;

      va_start(args, format);   
      vsnprintf(str, sizeof(str), format, args);
      va_end(args);

      const char *FileName = str;
      img.clear(); 
   
      std::string fname(FileName);

      if (fname.length() < 5)
         throw Exception("Unknown file format");

      FILE *f = fopen(fname.c_str(), "r");
      if (f == 0)
         throw FileNotFoundException("%s", fname.c_str());
      fclose(f);

      cv::Mat mat = cv::imread(fname, 0);

      if (mat.empty())
         throw Exception("Image file is invalid");

      copyMatToImage(mat, img);
   }

   void ImageUtils::saveImageToFile( const Image &img, const char *format, ... )
   {
      char str[MAX_LINE];
      va_list args;

      va_start(args, format);   
      vsnprintf(str, sizeof(str), format, args);
      va_end(args);

      std::string fname(str);
      cv::Mat mat;
      copyImageToMat(img, mat);
      cv::imwrite(fname, mat);
   }

   void ImageUtils::saveImageToBuffer( const Image &img, 
      const std::string &ext, std::vector<byte> &buffer )
   {
      cv::Mat mat;
      copyImageToMat(img, mat);
      cv::imencode(ext, mat, buffer);
   }
}