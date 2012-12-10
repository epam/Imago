#include "prefilter_retinex.h"
#include <opencv2/opencv.hpp>
#include "log_ext.h"
#include "image_utils.h"
#include "prefilter_basic.h"

namespace imago
{
	namespace prefilter_retinex
	{
		template <typename data_t>
		double contrastNormalizeSingleIteration(std::vector<data_t>& data, double drop_percentage = 0.01, double max_average = 128)
		{
			logEnterFunction();

			const int max_value = 255;	

			int hist[max_value+1] = {0};
			int min_v = 0;
			int max_v = max_value;
			double average = 0;

			for (size_t u = 0; u < data.size(); u++)
			{
				double v = data[u];
				hist[imago::round(v)]++;
				average += v;
			}

			average /= data.size();

			if (average > max_average)
			{
				getLogExt().append("Average value is OK", average);
				return average;
			}

			{
				int sum = 0;
				while (sum < data.size() * drop_percentage && max_v > min_v) 
				{
					sum += hist[max_v];
					max_v--;
				}
			}

			{
				int sum = 0;
				while (sum < data.size() * drop_percentage && max_v > min_v) 
				{
					sum += hist[min_v];
					min_v++;
				}
			}	

			min_v = -min_v;
			max_v = max_value + (max_value - max_v);
			getLogExt().append("Normalize range min", min_v);
			getLogExt().append("Normalize range max", max_v);
			getLogExt().append("Normalized average", average);

			cv::normalize(data, data, min_v, max_v, cv::NORM_MINMAX);

			average = 0;
			for (size_t u = 0; u < data.size(); u++)
			{
				data_t& v = data[u];
				if (v < 0)
					v = 0;
				else if (v > max_value)
					v = max_value;
				average += v;
			}
			average /= data.size();
			return average;
		}


		template <typename data_t>
		void contrastNormalize(std::vector<data_t>& data)
		{
			logEnterFunction();
			
			cv::normalize(data, data, 0, 255, cv::NORM_MINMAX);
			double prev_value = 0;
			for (int iters = 0; iters < 10; iters++)
			{
				double value = contrastNormalizeSingleIteration(data);
				if (value > 128 || value < prev_value)
					break;
				prev_value = value;
			}
		}

		double getAutoRetinexThreshold(double scale, double num_scales, double mean_diff)
		{
			return mean_diff * (1.5 * scale / num_scales + 0.5);
		}

		template <typename data_t>
		bool computeDLT(std::vector<data_t>& data_out, const std::vector<data_t>& data_in, size_t nx, size_t ny, double t)
		{
			logEnterFunction();

			const data_t* ptr_in = &data_in.at(0);
			const data_t* ptr_in_xm1 = ptr_in - 1;
			const data_t* ptr_in_xp1 = ptr_in + 1;
			const data_t* ptr_in_ym1 = ptr_in - nx;
			const data_t* ptr_in_yp1 = ptr_in + nx;
			data_t* ptr_out = &data_out.at(0);

			data_t diff = 0.0;

			for (size_t j = 0; j < ny; j++) 
			{
				for (size_t i = 0; i < nx; i++) 
				{
					*ptr_out = 0.;
					if (0 < i) {
						diff = *ptr_in - *ptr_in_xm1;
						if (fabs(diff) > t)
							*ptr_out += diff;
					}
					if (nx - 1 > i) {
						diff = *ptr_in - *ptr_in_xp1;
						if (fabs(diff) > t)
							*ptr_out += diff;
					}
					if (0 < j) {
						diff = *ptr_in - *ptr_in_ym1;
						if (fabs(diff) > t)
							*ptr_out += diff;
					}
					if ( ny - 1 > j) {
						diff = *ptr_in - *ptr_in_yp1;
						if (fabs(diff) > t)
							*ptr_out += diff;
					}
					ptr_in++;
					ptr_in_xm1++;
					ptr_in_xp1++;
					ptr_in_ym1++;
					ptr_in_yp1++;
					ptr_out++;
				}
			}

			return true;
		}

		template <typename data_t>
		bool fastFillCosTable(size_t size, std::vector<data_t>& table)
		{   
			logEnterFunction();

			table.resize(size);

			data_t* ptr_table = &table.at(0);
			for (size_t i = 0; i < size; i++)
				*ptr_table++ = (data_t)cos((imago::PI * i) / size);

			return true;
		}

		template <typename data_t>
		bool retinexPoissonDCT(std::vector<data_t>& data, size_t nx, size_t ny, data_t m)
		{
			logEnterFunction();

			std::vector<data_t> cosi, cosj;
			fastFillCosTable(nx, cosi);
			fastFillCosTable(ny, cosj);

			data_t m2 = (data_t)(m / 2.0);
			data_t* ptr_data = &data.at(0);
			data_t* ptr_cosi = &cosi.at(0);
			data_t* ptr_cosj = &cosj.at(0);

			*ptr_data++ = 0.;
			ptr_cosi++;

			for (size_t i = 1; i < nx; i++)
			{
				*ptr_data++ *= (data_t)(m2 / (2. - *ptr_cosi++ - *ptr_cosj));
			}

			ptr_cosj++;
			ptr_cosi = &cosi.at(0);

			for (size_t j = 1; j < ny; j++)
			{
				for (size_t i = 0; i < nx; i++)
				{
					*ptr_data++ *= (data_t)(m2 / (2. - *ptr_cosi++ - *ptr_cosj));
				}
				ptr_cosj++;
				ptr_cosi = &cosi.at(0);
			}

			return true;
		}

		template <typename data_t>
		void cvBasedCDT(const std::vector<data_t>& data, size_t nx, size_t ny, std::vector<data_t>& output, int flags = 0)
		{
			logEnterFunction();

			// TODO: libfftw3 is more than twice faster

			cv::Mat1d temp_in(ny,nx);
			cv::Mat1d temp_out;
			for (size_t x = 0; x < nx; x++)
				for (size_t y = 0; y < ny; y++)
					temp_in(y,x) = data[x + nx*y];

			cv::dct(temp_in, temp_out, flags);

			for (size_t x = 0; x < nx; x++)
				for (size_t y = 0; y < ny; y++)
					output[x + nx*y] = (data_t)temp_out(y,x);
		}


		template <typename data_t>
		bool retinexProcess(std::vector<data_t>& data, size_t nx, size_t ny, double thresh)
		{
			logEnterFunction();
			std::vector<data_t> temp(data.size());

			getLogExt().appendText("Compute discrete laplacian threshold");
			computeDLT(temp, data, nx, ny, thresh); // data -> temp

			getLogExt().appendText("Compute simple discrete cosine transform");
			cvBasedCDT(temp, nx, ny, temp); // temp -> temp
 
			getLogExt().appendText("Solve the Poisson PDE in Fourier space");
			data_t normDCT = (data_t)(1.0 / (data_t)(nx * ny));			
			retinexPoissonDCT(temp, nx, ny, normDCT); // temp -> temp
	
			getLogExt().appendText("Compute inversed discrete cosine transform");
			cvBasedCDT(temp, nx, ny, data, cv::DCT_INVERSE); // temp -> data

			return true;
		}		

		bool prefilterRetinex(Settings& vars, Image& raw)
		{
			logEnterFunction();

			getLogExt().appendImage("Source image", raw);

			// dimensions should be even for the FFT transform
			int width = (raw.getWidth() / 2) * 2;
			int height = (raw.getHeight() / 2) * 2;

			typedef std::vector<float> Array;
			
			Array result(width * height);

			// process multi-scale retinex
			{
				Array input(width * height);

				for (int y = 0; y < height; y++)
					for (int x = 0; x < width; x++)
						input[y * width + x] = raw.getByte(x, y);

				for (int iteration = 1; iteration < 16; iteration += 2)
				{
					getLogExt().append("Iteration", iteration);

					Array temp = input;
					double threshold = iteration;
					retinexProcess(temp, width, height, threshold);
					for (size_t u = 0; u < temp.size(); u++)
						result[u] += temp[u];
				}
			}

			// normalize contrast
			contrastNormalize(result);

			// store result back
			getLogExt().appendText("Store image data");
			raw.crop(0, 0, width - 1, height - 1); // TODO: slow
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					int c = imago::round(result[y * width + x]);
					if (c < 0)
						c = 0;
					else if (c > 255)
						c = 255;
					raw.getByte(x, y) = c;
				}
			}

			getLogExt().appendImage("Retinex-processed image", raw);

			// call the basic prefilter
			prefilter_cv::prefilterBasic(vars, raw);
			
			return true;
		}
	}
}