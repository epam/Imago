#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include "opencv2\opencv.hpp"

#include "segment.h"
#include "image_utils.h"
#include "contour_extractor.h"
#include "stl_fwd.h"
#include "prefilter_cv.h"
#include "contour_template.h"
#include "log_ext.h"

using std::string;
using std::cout;
using std::vector;
using std::ofstream;
using std::ostream_iterator;
namespace po = boost::program_options;
namespace fs = boost::filesystem;

imago::ComplexContour calc_shape_contours(imago::Settings &vars, const fs::path &p)
{
	imago::Segment img;
	imago::ImageUtils::loadImageFromFile(img, "%s", p.string().c_str());
	vars.general.ImageWidth =  img.getWidth();
	vars.general.ImageHeight = img.getHeight();

	imago::ComplexContour cc;
	try
	{
		cc = imago::ComplexContour::RetrieveContour(vars, img);
	}
	catch(std::exception e)
	{
		return cc;
	}
	return cc;
}

void SaveMatrix(ofstream &out, cv::Mat &mat, std::string &caption )
{
	out << "double ";
	out << caption << " [" << mat.rows << "][";
	out << mat.cols << "] = { \n";

	for(int i = 0; i < mat.rows; i++ )
	{
		out << "{ ";
		for(int j = 0; j < mat.cols; j++)
			if(j == (mat.cols - 1))
				out << mat.at<double>(i, j);
			else
				out << mat.at<double>(i, j) << ", ";
		if(i == (mat.rows - 1))
			out << " } \n";
		else
			out << "}, \n";
	}	   
	out << "} \n";
}


int getAngleDirection3(imago::ComplexNumber vec)
{
	double pi_8 = imago::PI / 8.0;
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
	return 0;
}

void ProcessMatrix(cv::Ptr<cv::FilterEngine> filt, cv::Mat src, cv::Mat &dest, int rowBorderType, int colBorderType)
{
	double sum = 0.0;

	double gaussian[3][3] = {	{0.0751,    0.1238,    0.0751},
								{0.1238,    0.2042,    0.1238},
								{0.0751,    0.1238,    0.0751}};

#define GET_VAL(m, n) \
	src.at<double>(cv::borderInterpolate((m), src.rows, colBorderType), cv::borderInterpolate((n), src.cols, rowBorderType))


	for(int i = 0; i < src.rows; i++)
		for(int j = 0; j < src.cols; j++)
		{
			//double val = matr.at<double>(cv::borderInterpolate(i - 1, matr.rows, cv::BORDER_WRAP),
            //              cv::borderInterpolate(j-1, matr.cols, cv::BORDER_REPLICATE));
			dest.at<double>(i, j) = GET_VAL(i - 1, j - 1) * gaussian[0][0] + GET_VAL(i - 1, j ) * gaussian[0][1] + GET_VAL(i - 1, j + 1) * gaussian[0][2] + 
				GET_VAL(i, j - 1) * gaussian[1][0] + GET_VAL(i, j ) * gaussian[1][1] + GET_VAL(i, j + 1) * gaussian[1][2] +
				GET_VAL(i + 1, j - 1) * gaussian[0][0] + GET_VAL(i + 1, j ) * gaussian[0][1] + GET_VAL(i + 1, j + 1) * gaussian[0][2];
		}

#undef GET_VAL

	//filt->apply(src, dest);


	for(int i = 0; i < dest.rows; i++)
		for(int j = 0; j < dest.cols; j++)
			   sum += dest.at<double>(i, j);

	for(int i = 0; i < dest.rows; i++)
		for(int j = 0; j < dest.cols; j++)
			   dest.at<double>(i, j) = dest.at<double>(i, j) / sum;

	for(int i = 0; i < dest.rows; i++)
		for(int j = 0; j < dest.cols; j++)
			if(dest.at<double>(i, j) < imago::EPS)
				dest.at<double>(i, j) = imago::EPS;
}

int main(int argc, char **argv)
{
	string data;
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

	int angleChange[8][8] = {	
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0} };
   //int count; 
   string output; //, contours_output, shape_contours_out;
   po::options_description opts("Allowed options");

   opts.add_options()
      ("help", "Prints help message")
      ("data-path,D", po::value<string>(&data), "Path to the directory with symbols images")
	  ("output-name,O", po::value<string>(&output), "Output file name");

   imago::Settings vars;

   po::variables_map vm;
   po::store(po::parse_command_line(argc, argv, opts), vm);
   po::notify(vm);

   if (vm.count("help"))
   {
      cout << opts << "\n";
      return 1;
   }

   if (!vm.count("data-path") || !(vm.count("output-name") ))
   {
      cout << "Wrong command line arguments.\n";
      cout << opts << "\n";
      return 1;
   }


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
   
   if( output.compare("") != 0 )
   {
		imago::getLogExt().setLoggingEnabled(vars.general.LogEnabled);

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
	   
	   //accumulate matrix values
	   BOOST_FOREACH(fs::path p, files)
	   {

		   imago::ComplexContour contour = calc_shape_contours(vars, p);
		   //*scontours_out << (contour.Size() * 2) << "\n";

		   std::vector<double> dc;
		    
		   for(int i = 0; i <  contour.Size(); i++)
		   {
			   imago::ComplexNumber cc = contour.getContour(i);
			   dc.push_back(cc.getReal());
			   dc.push_back(cc.getImaginary());
		   }

		   contour.NormalizeByPerimeter();
		   for(int i = 0; i <  contour.Size(); i++)
		   {
			   imago::ComplexNumber cc = contour.getContour(i);
			   
			   int binD = getAngleDirection3(cc);
			   vecDir[binD]++;
			   int binS = ((int)(cc.getRadius() * 10)) % 10;
			   vecSize[binS]++;
			   jointSizeDir[binD][binS]++;

			   int binD2 = getAngleDirection3(contour.getContour(i+1));

			   angleChange[binD][binD2]++;
		   }

		  //std::copy(dc.begin(), dc.end(), ostream_iterator<double>(*scontours_out , " "));
		  //*scontours_out  << "\n";
		  
	   }

	   //TODO: smooth/normalize matrices
	   cv::Mat matr(8, 10, CV_64F), dest(8, 10, CV_64F);

	   cv::Ptr<cv::FilterEngine> filtE = cv::createSeparableLinearFilter(CV_64F,
		   CV_64F,
		   cv::getGaussianKernel(3, 1),
		   cv::getGaussianKernel(3, 1),
		   cv::Point(-1, -1),
		   0.0,
		   cv::BORDER_WRAP,
		   cv::BORDER_REPLICATE);

	   for(int i = 0; i < 8; i++)
		   for(int j = 0; j < 10; j++)
			   matr.at<double>(i, j) = (double)jointSizeDir[i][j];
	   
	   SaveMatrix(out, matr, string("NotProcessed"));

	   /*cv::Mat preMat(10, 12, CV_64F);

	   for(int i = 0; i < 10; i++)
		   for(int j = 0; j < 12; j++)
			   preMat.at<double>(i, j) = matr.at<double>(cv::borderInterpolate(i - 1, matr.rows, cv::BORDER_WRAP),
                          cv::borderInterpolate(j-1, matr.cols, cv::BORDER_REPLICATE));
	   SaveMatrix(out, preMat, string("InterpolatedBorders"));

	   filtE->apply(matr, dest);

	   SaveMatrix(out, dest, string("Filtered"));*/

	   ProcessMatrix(filtE, matr, dest, cv::BORDER_REPLICATE, cv::BORDER_WRAP);

	   //TODO: save matrices to files
	   SaveMatrix(out, dest, string("jointSizeDir"));
	   

	   cv::Mat matr2(8, 8, CV_64F), dest2(8, 8, CV_64F);
	   
	   for(int i = 0; i < 8; i++)
		   for(int j = 0; j < 8; j++)
			   matr2.at<double>(i, j) = (double)angleChange[i][j];

	   ProcessMatrix(filtE, matr2, dest2, cv::BORDER_REPLICATE, cv::BORDER_REPLICATE);

	   SaveMatrix(out, dest2, string("transition"));

	   out.close();
	   //imago::SessionManager::getInstance().releaseSID(sid); 
	   return 0;
   }

  
   out.close();
   return 0;
}