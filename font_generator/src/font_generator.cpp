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
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

#include "segment.h"
#include "image_utils.h"
#include "contour_extractor.h"
#include "stl_fwd.h"
#include "contour_template.h"
#include "session_manager.h"
#include "current_session.h"

using std::string;
using std::cout;
using std::vector;
using std::ofstream;
using std::ostream_iterator;
namespace po = boost::program_options;
namespace fs = boost::filesystem;

imago::SymbolFeatures calc_features(const fs::path &p, int count) 
{
   imago::Segment img;
   imago::ImageUtils::loadImageFromFile(img, "%s", p.string().c_str());

   img.initFeatures(count);
   return img.getFeatures();
}

imago::Points2i calc_contours(const fs::path &p) 
{
   imago::Segment img;
   imago::ImageUtils::loadImageFromFile(img, "%s", p.string().c_str());

   imago::Points2i contour;
   imago::ContourExtractor().getApproxContour(img, contour);
   return contour;
}

imago::ComplexContour calc_shape_contours(const fs::path &p)
{
	imago::Segment img;
	imago::ImageUtils::loadImageFromFile(img, "%s", p.string().c_str());
	imago::getSettings().set("imgWidth", img.getWidth());
			imago::getSettings().set("imgHeight", img.getHeight());

	imago::ComplexContour cc = imago::ComplexContour::RetrieveContour(img);
	return cc;
}

int getAngleDirection(imago::ComplexNumber vec)
{
	double pi_8 = imago::PI_4 / 2.0;
	double angle = vec.getAngle();
		if(angle < 0)
			angle  += 2 * imago::PI;
		
		if(angle < pi_8 || angle >= 15.0 * pi_8)
			return 0;//"E";
		else
			if(angle >= pi_8 && angle < 3.0 * pi_8)
				return 1;// "NE";
			else
				if(angle >= 3.0 * pi_8 && angle < pi_8 * 5.0)
					return 2; // "N";
				else
					if(angle >= pi_8 * 5.0 && angle < pi_8 * 7.0)
						return 3; // "NW";
					else
						if(angle >= pi_8 * 7.0 && angle < pi_8 * 9.0)
							return 4; // "W";
		
		if(angle >= 9.0 * pi_8 && angle < 11.0 * pi_8)
				return 5; // "SW";
			else
				if(angle >= 11.0 * pi_8 && angle < pi_8 * 13.0)
					return 6; // "S";
				else
					if(angle >= pi_8 * 13.0 && angle < pi_8 * 15.0)
						return 7; // "SE";

}

int main(int argc, char **argv)
{
   string data;
   int count; 
   string output, contours_output, shape_contours_out;
   po::options_description opts("Allowed options");

   opts.add_options()
      ("help", "Prints help message")
      ("data-path,D", po::value<string>(&data), "Path to the directory with symbols images")
      ("count", po::value<int>(&count)->default_value(25), "Count of descriptor pairs")
      ("output-name,O", po::value<string>(&output), "Output file name")
      ("output-contours-name,C", po::value<string>(&contours_output), "Contours output file name")
	  ("output-shapes-name,S", po::value<string>(&shape_contours_out), "Shape contours output file name");

   po::variables_map vm;
   po::store(po::parse_command_line(argc, argv, opts), vm);
   po::notify(vm);

   if (vm.count("help"))
   {
      cout << opts << "\n";
      return 1;
   }

   if (!vm.count("data-path") || !(vm.count("output-name") || vm.count("output-shapes-name")))
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
   chars += "$%^&+-";

   ofstream out(output);
   std::auto_ptr<ofstream> contours_out;
   if (vm.count("output-contours-name"))
      contours_out.reset(new ofstream(contours_output));
   //std::ostream &out = cout;

   std::auto_ptr<ofstream> scontours_out;
   if(vm.count("output-shapes-name"))
	   scontours_out.reset(new ofstream(shape_contours_out));

   if(scontours_out.get())
   {
	   qword sid = imago::SessionManager::getInstance().allocSID();
		imago::SessionManager::getInstance().setSID(sid);
		imago::getSettings()["DebugSession"] = true;


	   vector<fs::path> files;
	   if(0)
	   {
	   BOOST_FOREACH(char c, chars)
	   {
		   fs::path p(data);
		   if (c >= 'A' && c <= 'Z')
			 p /= string("capital/") + c;
		   else
			 p /= string() + c;

		   fs::directory_iterator di(p), di_end;
		   
		   for (; di != di_end; ++di)
		   {
			   printf("%s \n", di->path().string().c_str());
			   if(di->path().extension() != ".png")
				   continue;
         
			   files.push_back(di->path());
		   }
	   }
	   }
	   else
	   {
		   fs::path p(data);
		   
		   fs::directory_iterator di(p), di_end;
		   
		   for (; di != di_end; ++di)
		   {
			   printf("%s \n", di->path().string().c_str());
			   if(di->path().extension() != ".png")
				   continue;
         
			   files.push_back(di->path());
		   }
	   }
	   
	   *scontours_out << files.size() << "\n";
	   
	   int vecSize[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0 , 0};
	   int vecDir[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	   int jointSizeDir[8][10] = {	{0, 0, 0, 0, 0, 0, 0, 0, 0 , 0},
	   {0, 0, 0, 0, 0, 0, 0, 0, 0 , 0},
	   {0, 0, 0, 0, 0, 0, 0, 0, 0 , 0},
	   {0, 0, 0, 0, 0, 0, 0, 0, 0 , 0},
	   {0, 0, 0, 0, 0, 0, 0, 0, 0 , 0},
	   {0, 0, 0, 0, 0, 0, 0, 0, 0 , 0},
	   {0, 0, 0, 0, 0, 0, 0, 0, 0 , 0},
	   {0, 0, 0, 0, 0, 0, 0, 0, 0 , 0} };

	   BOOST_FOREACH(fs::path p, files)
	   {

		   imago::ComplexContour contour = calc_shape_contours(p);
		   *scontours_out << (contour.Size() * 2) << "\n";

		   std::vector<double> dc;
		    
		   for(int i = 0; i <  contour.Size(); i++)
		   {
			   imago::ComplexNumber cc = contour.getContour(i);
			   dc.push_back(cc.getReal());
			   dc.push_back(cc.getImaginary());
		   }

		   contour.Normalize();
		   for(int i = 0; i <  contour.Size(); i++)
		   {
			   imago::ComplexNumber cc = contour.getContour(i);
			   
			   int binD = getAngleDirection(cc);
			   vecDir[binD]++;
			   int binS = ((int)(cc.getRadius() * 10)) % 10;
			   vecSize[binS]++;
			   jointSizeDir[binD][binS]++;
		   }

		  std::copy(dc.begin(), dc.end(), ostream_iterator<double>(*scontours_out , " "));
		  *scontours_out  << "\n";
		  
	   }

	   out.close();
	   imago::SessionManager::getInstance().releaseSID(sid); 
	   return 0;
   }

   out << count << " " << chars.length() << "\n";
   BOOST_FOREACH(char c, chars)
   {
      fs::path p(data);
      if (c >= 'A' && c <= 'Z')
         p /= string("capital/") + c;
      else
         p /= string() + c;

      fs::directory_iterator di(p), di_end;
      vector<fs::path> files;
      for (; di != di_end; ++di)
      {
         if(di->path().extension() != ".png")
            continue;
         
         files.push_back(di->path());
      }

      cout << c << "\n";
      out << c << " " << files.size() << "\n";

      if (contours_out.get())
         *contours_out << c << " " << files.size() << "\n";

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