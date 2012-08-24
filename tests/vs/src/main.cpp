#include <iostream>

#include "comdef.h"
#include "chemical_structure_recognizer.h"
#include "image_utils.h"
#include "superatom_expansion.h"
#include "prefilter_cv.h"
#include "output.h"
#include "molecule.h"

using namespace imago;

extern "C" DLLEXPORT int recognize(char* image, int image_width, int image_height,
	                                           char* output_buffer, int output_buffer_size,
											   int* recognition_warnings, int* reserved)
{
	if (!image_width || !image_height || !image || !output_buffer || !output_buffer_size)
	{
		return 2;
	}

	try
	{
		Image img;
		img.init(image_width, image_height);
		for (int y = 0; y < image_height; y++)
		{
			for (int x = 0; x < image_width; x++)
			{
				img.getByte(x,y) = image[x + y * image_width];
			}
		}

		ChemicalStructureRecognizer csr;

		Settings vars;

		prefilterEntrypoint(vars, img);
		Molecule mol;

		csr.image2mol(vars, img, mol);
		if (recognition_warnings)
			*recognition_warnings = mol.getWarningsCount();

		std::string molfile = expandSuperatoms(vars, mol);
		memset(output_buffer, 0, output_buffer_size);
		memcpy(output_buffer, molfile.c_str(), std::min(output_buffer_size, (int)molfile.size() ) );
		
	}
	catch (std::exception&)
	{
		return 1;
	}

	return 0;
}
