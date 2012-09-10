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

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <opencv2/opencv.hpp>

#include "segment.h"
#include "image_utils.h"
#include "contour_extractor.h"
#include "stl_fwd.h"
#include "prefilter_cv.h"

using std::string;
using std::cout;
using std::vector;
using std::ofstream;
using std::ostream_iterator;
namespace po = boost::program_options;
namespace fs = boost::filesystem;

void prefilter(imago::Segment& img, int threshold)
{
	for (int x = 0; x < img.getWidth(); x++)
		for (int y = 0; y < img.getHeight(); y++)
			if (img.getByte(x,y) < threshold)
				img.getByte(x,y) = 0;
			else
				img.getByte(x,y) = 255;
}

imago::SymbolFeatures calc_features(const fs::path &p, int count) 
{
   imago::Segment img;
   imago::ImageUtils::loadImageFromFile(img, "%s", p.string().c_str());
      
   imago::Settings vars;
   prefilter(img, vars.characters.Filter_Threshold_generator);
   img.initFeatures(count, vars.characters.Contour_Eps1_generator, vars.characters.Contour_Eps2_generator);

   return img.getFeatures();
}

imago::IntDeque calc_templates(const fs::path &p)
{
	imago::Segment img, resImg;
	cv::Mat cv_img, cv_reimg(15, 10, CV_8U);
	imago::ImageUtils::loadImageFromFile(img, "%s", p.string().c_str());
	imago::ImageUtils::copyImageToMat(img, cv_img);
	cv::resize(cv_img, cv_reimg, cv_reimg.size()) ;

	imago::IntDeque img_templ;

	for(int i = 0; i < cv_reimg.cols; i++)
		for(int j = 0; j < cv_reimg.rows; j++)
			img_templ.push_back(cv_reimg.at<unsigned char>(cv::Point(i, j)));
	return img_templ;
}

imago::Points2i calc_contours(const fs::path &p) 
{
   imago::Segment img;
   imago::ImageUtils::loadImageFromFile(img, "%s", p.string().c_str());
   
   imago::Settings vars;
   prefilter(img, vars.characters.Filter_Threshold_generator);

   imago::Points2i contour;
   imago::ContourExtractor().getApproxContour(img, contour, vars.characters.Contour_Eps1_generator, vars.characters.Contour_Eps2_generator);
   return contour;
}

int main(int argc, char **argv)
{
   string data;
   int count; 
   string output, contours_output, templates_output;
   po::options_description opts("Allowed options");

   opts.add_options()
      ("help", "Prints help message")
      ("data-path,D", po::value<string>(&data), "Path to the directory with symbols images")
      ("count", po::value<int>(&count)->default_value(25), "Count of descriptor pairs")
      ("output-name,O", po::value<string>(&output), "Output file name")
      ("output-contours-name,C", po::value<string>(&contours_output), "Contours output file name")
      ("output-templates-name,T", po::value<string>(&templates_output), "Templates output file name");

   po::variables_map vm;
   po::store(po::parse_command_line(argc, argv, opts), vm);
   po::notify(vm);

   if (vm.count("help"))
   {
      cout << opts << "\n";
      return 1;
   }

   if (!vm.count("data-path") || !vm.count("output-name"))
   {
      cout << "Wrong command line arguments.\n";
      cout << opts << "\n";
      return 1;
   }

   //cout << fs::current_path() << "\n";

   if (!fs::exists(data) || !fs::is_directory(data))
   {
      cout << data << " is not a directory." << "\n";
      return 1;
   }

   string chars;
   for (char c = 'A'; c <= 'Z'; ++c)
      chars += c;
   for (char c = 'a'; c <= 'z'; ++c)
      chars += c;
   for (char c = '0'; c <= '9'; ++c)
      chars += c;

   chars += "$%^&#+-="; // tricky

   ofstream out(output.c_str(), std::ios::out);
   std::auto_ptr<ofstream> contours_out;
   std::auto_ptr<ofstream> templates_out;
   if (vm.count("output-contours-name"))
      contours_out.reset(new ofstream(contours_output.c_str(), std::ios::out));
   //std::ostream &out = cout;
   if(vm.count("output-templates-name"))
	   templates_out.reset(new ofstream(templates_output.c_str(), std::ios::out));

   out << count << " " << chars.length() << "\n";
   BOOST_FOREACH(char c, chars)
   {
      fs::path p(data);
      if (c >= 'A' && c <= 'Z')
         p /= string("capital/") + c;
      else
         p /= string() + c;

	  vector<fs::path> files;

	  try
	  {
		  fs::directory_iterator di(p), di_end;
	 
		  for (; di != di_end; ++di)
		  {
			 if(di->path().extension() != ".png")
				continue;
		  
			 files.push_back(di->path());
		  }
	  }
	  catch(std::exception exc)
	  {
		  continue;
	  }

      cout << c << "\n";
      out << c << " " << files.size() << "\n";

      if (contours_out.get())
         *contours_out << c << " " << files.size() << "\n";
	  
	  if(templates_out.get())
		  *templates_out << c << " " << files.size() << "\n";

      BOOST_FOREACH(fs::path p, files)
      {
		  
		  imago::SymbolFeatures sf = calc_features(p, count);
		  out << sf.inner_contours_count << "\n";

         std::copy(sf.descriptors.begin(), sf.descriptors.end(), ostream_iterator<double>(out, " "));
         out << "\n";
         for (int i = 0; i < sf.inner_contours_count; ++i)
         {
            std::copy(sf.inner_descriptors[i].begin(), sf.inner_descriptors[i].end(), ostream_iterator<double>(out, " "));
            out << "\n";
         }

		 if(templates_out.get())
		 {
			 imago::IntDeque templ = calc_templates(p);
			 std::copy(templ.begin(), templ.end(), ostream_iterator<int>(*templates_out, " "));
			 *templates_out << "\n";
		 }
         if (contours_out.get())
         {
            imago::Points2i contour = calc_contours(p);
            *contours_out << contour.size() << "\n";
            BOOST_FOREACH(imago::Vec2i point, contour)
            {
               *contours_out << point.x << " " << point.y << " ";
            }
            *contours_out << "\n";
         }
      }
   }
 
   out.close();
   return 0;
}
