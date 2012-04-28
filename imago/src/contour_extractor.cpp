#include <vector>
#include <deque>
#include <cmath>

#include "contour_extractor.h"
#include "image.h"
#include "binarizer.h"
#include "vec2d.h"
#include "exception.h"
#include "algebra.h"
#include "constants.h"

namespace imago
{
   ContourExtractor::ContourExtractor()
   {
   }

   ContourExtractor::~ContourExtractor()
   {
   }

   void ContourExtractor::getRawContour( const Image &image, Points2i &contour )
   {
      Image img;
      img.copy(image);
      Binarizer(img, 190).apply();

      int w = img.getWidth(), h = img.getHeight(),
          k = (h + 1) * (w + 1), begin = 0, x, y, i;
      byte ul, ur, dl, dr;
      std::deque<int> prev(k, -1);
      double dist = 0;
      double min_dist = 1e16;
      for (i = 0; i < w * h; i++)
      {
         if (img[i] != 255)
         {
            y = i / w;
            x = i % w;
            //begin = y * (w + 1) + x;

            dist = sqrt((double)x * x + y * y);
            //dist = x + y;
            if (min_dist - dist > EPS)
            //if (dist < min_dist)
            {
               min_dist = dist;
               begin = i + i / w;
            }

            //begin = i + i / w;
            //break;
         }
      }

      std::deque<int> stack;
      int cur, p = 0;
      int t = 0, s = 0;
      int next[4] = { -1, -1, -1, -1 };
      int delta;
      int first;
      first = begin + 1;
      y = first / (w + 1);
      x = first % (w + 1);

      if (begin >= w + 2 && img[first - 1 - y] != 255 &&
          img[first - w - 1 - (y - 1)] != 255 && img[first - y] != 0 &&
          img[first - w - 1 - 1 - (y - 1)] != 0)
      {
         first -= w + 1;
      }

      cur = first;
      stack.push_back(cur);
      int iterations = 0;
      while (true)
      {
         iterations++;
         if (iterations > k)
            throw NoContourException("infinite loop");

         if (stack.size() == 0)
            throw NoContourException();

         cur = stack.back();
         stack.pop_back();

         prev[cur] = p;
         delta = cur - p;

         if (cur == begin)
            break;

         y = cur / (w + 1);
         x = cur % (w + 1);

         if (y > 0 && y < h && x > 0 && x < w)
         {
            if (img[cur - y] != 255 && img[cur - w - 1 - 1 - (y - 1)] != 255
                && img[cur - 1 - y] != 0 && img[cur - w - 1 - (y - 1)] != 0)
            {
               if (delta == w + 1 || delta == w)
                  t = cur + 1;
               else if (delta == -1) // || delta == w + 2
                  t = cur - w - 1;
               else if (delta == -(w + 1) || delta == -w)
                  t = cur - 1;
               else if (delta == 1) // || delta == -(w + 2)
                  t = cur + w + 1;

               prev[cur] = -1;
               stack.push_back(t);
               continue;
            }

            if (img[cur - 1 - y] != 255 && img[cur - w - 1 - (y - 1)] != 255
                && img[cur - y] != 0 && img[cur - w - 1 - 1 - (y - 1)] != 0)
            {
               if (delta == w + 1) // || delta == w
                  t = cur - 1;
               else if (delta == -1 || delta == -(w + 2))
                  t = cur + w + 1;
               else if (delta == -(w + 1)) // || delta == -w
                  t = cur + 1;
               else if (delta == 1 || delta == w + 2)
                  t = cur - (w + 1);

               prev[cur] = -1;
               stack.push_back(t);
               continue;
            }
         }

         if (delta == 1 || delta == (w + 2))
            s = 4;
         else if (delta == (w + 1) || delta == w || delta == 2 * (w + 1))
            s = 3;
         else if (delta == -1 || delta == -(w + 2))
            s = 2;
         else if (delta == -(w + 1) || delta == -w || delta == -2 * (w + 1))
            s = 1;

         //Where can we go from there
         ul = (x - 1 >= 0 && y - 1 >= 0) ? img.getByte(x - 1, y - 1) : 255;
         ur = (x < w && y - 1 >= 0) ? img.getByte(x, y - 1) : 255;
         dl = (x - 1 >= 0 && y < h) ? img.getByte(x - 1, y) : 255;
         dr = (x < w && y < h) ? img.getByte(x, y) : 255;

         if (y - 1 >= 0 && (ul - ur) != 0)
         {
            next[(s + 0) % 4] = cur - w - 1;
         }
         if (x + 1 < w + 1 && (ur - dr) != 0)
         {
            next[(s + 1) % 4] = cur + 1;
         }
         if (y + 1 < h + 1 && (dr - dl) != 0)
         {
            next[(s + 2) % 4] = cur + w + 1;
         }
         if (x - 1 >= 0 && (dl - ul) != 0)
         {
            next[(s + 3) % 4] = cur - 1;
         }

         for (i = 3; i >= 0; i--)
         {
            if (next[i] != -1)
            {
               if (prev[next[i]] == -1)
                  stack.push_back(next[i]);
               next[i] = -1;
            }
         }

         p = cur;
      }

      IntDeque pts;
      cur = prev[begin];
      do
      {
         pts.push_back(cur);
         cur = prev[cur];
      } while (cur != first);
      pts.push_back(begin);

      contour.clear();
      for (IntDeque::reverse_iterator it = pts.rbegin();
           it != pts.rend(); ++it)
      {
         contour.push_back(Vec2i(*it % (w + 1), *it / (w + 1)));
      }
      contour.push_back(Vec2i(contour[0]));
   }

   void ContourExtractor::getApproxContour( const Image &i, Points2i &contour )
   {
      getRawContour(i, contour);
      _approximize(contour);
   }

   void ContourExtractor::_approximize( Points2i &contour )
   {
	   double epsilons[2] = { consts::ContourExtractor::ApproxEps1, consts::ContourExtractor::ApproxEps2 };
      for (int l = 0; l < 2; l++)
      {
         int i = 1;
         double epsilon = epsilons[l];

         while (i < (int)contour.size() - 2)
         {
            int j, k;
            j = i + 1;
            bool flag = 1;
            while (j < (int)contour.size() - 1 && flag)
            {
               j++;
               for (k = i + 1; k < j; k++)
               {
                  if (Algebra::distance2segment(contour[k], contour[i],
                                                contour[j]) > epsilon)
                  {
                     flag = false;
                     break;
                  }
               }
            }
            j--;

            for (k = i + 1; k < j; k++)
               contour.erase(contour.begin() + (i + 1));

            i++;
         }
      }

      contour.pop_back();
   }
}
