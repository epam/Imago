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
#include <cstring>
#include <string>

#include "imago_c.h"
#include "indigo.h"
#include "image_utils.h"
#include "molfile_saver.h"
#include "log_ext.h"
#include "exception.h"
#include "output.h"
#include "scanner.h"
#include "comdef.h"
#include "session_manager.h"
#include "current_session.h"
#include "superatom_expansion.h"
#include "settings.h"
#include "failsafe_png.h"

#define IMAGO_BEGIN try {                                                    

#define IMAGO_END   } catch ( ImagoException &e )                                 \
                    {                                                        \
                       RecognitionContext *context =                         \
                          (RecognitionContext*)gSession.get()->context();    \
                       std::string &error_buf = context->error_buf;          \
                       error_buf.erase();                                    \
                       ArrayOutput aout(error_buf);                          \
                       aout.writeStringZ(e.what());                          \
                       return 0;                                             \
                    }                                                        \
                    return 1;

namespace imago
{
   void prefilterEntrypoint(Settings& vars, Image& raw);
}

using namespace imago;

struct RecognitionContext
{
   Image img;
   Molecule mol;
   std::string molfile;
   std::string out_buf;
   std::string error_buf;
   Settings vars;
   void *session_specific_data;
   RecognitionContext () 
   {
      session_specific_data = 0;

      ArrayOutput aout(error_buf);
      aout.writeStringZ("No error");
   }
};

CEXPORT qword imagoAllocSessionId()
{
   return SessionManager::getInstance().allocSID();
}

CEXPORT void imagoSetSessionId( qword id )
{
   SessionManager::getInstance().setSID(id);
   indigoSetSessionId(id);
   RecognitionContext *&context = (RecognitionContext *&)gSession.get()->context(); 
   
   if (context == 0)
      context = new RecognitionContext();
}

CEXPORT void imagoReleaseSessionId( qword id )
{
   indigoReleaseSessionId(id);
   RecognitionContext *context;
   if ((context = (RecognitionContext*)gSession.get()->context()) != 0)
   {
      delete context;
      gSession.get()->context() = 0;
   }
   SessionManager::getInstance().releaseSID(id);
}

CEXPORT int imagoGetConfigsCount()
{  
	return imago::ctClustersTotalCount;
}

CEXPORT int imagoSetConfigNumber( const int number )
{
   IMAGO_BEGIN;

   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   context->vars.updateCluster((ClusterType)number);

   IMAGO_END;
}

CEXPORT int imagoSetFilter( const char *Name )
{
	IMAGO_BEGIN;

   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   bool found = false;
   for (int i = ftStd; i <= ftPass; i++)
	   if (strcmp(Name, FilterName[i]) == 0)
	   {
		   context->vars.general.DefaultFilterType = (FilterType)i;
		   found = true;
	   }

	if (!found)
		throw ImagoException(std::string("Filter not found: ") + Name);

   IMAGO_END;
}


CEXPORT int imagoLoadImageFromFile( const char *FileName )
{
   IMAGO_BEGIN;

   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   ImageUtils::loadImageFromFile(context->img, FileName);
      
   IMAGO_END;
}

CEXPORT int imagoFilterImage()
{
   IMAGO_BEGIN;
   
   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   prefilterEntrypoint(context->vars, context->img);

   IMAGO_END;
}

CEXPORT int imagoLoadImageFromBuffer( const char *buf, const int buf_size )
{
   IMAGO_BEGIN;
   
   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   const unsigned char* buf_uc = (const unsigned char*)buf;
   failsafePngLoadBuffer(buf_uc, buf_size, context->img);

   IMAGO_END;
}

CEXPORT int imagoLoadGreyscaleRawImage( const char *buf, const int width, const int height )
{
   IMAGO_BEGIN;

   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   Image &img = context->img;

   img.clear();

   img.init(width, height);
   
   for (int i = 0; i < width * height; i++)
      img[i] = buf[i];

   IMAGO_END;
}

CEXPORT int imagoGetInkPercentage(double *result)
{
	IMAGO_BEGIN;
	RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
	Image &img = context->img;
	
	size_t ink = 0;
	size_t total = img.getWidth() * img.getHeight();
	for (int y = 0; y < img.getHeight(); y++)
	{
		for (int x = 0; x < img.getWidth(); x++)
		{
			if (img.getByte(x,y) < 64)
				ink++;			
		}
	}

	if (result)
	{
		if (total > 0)
			*result = (double)ink / (double)total;
		else
			*result = 0;
	}
   
	IMAGO_END;
}

CEXPORT int imagoGetPrefilteredImageSize (int *width, int *height)
{
   IMAGO_BEGIN;
   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   Image &img = context->img;

   *height = img.getHeight();
   *width = img.getWidth();
   IMAGO_END;
}

CEXPORT int imagoGetPrefilteredImage (unsigned char **data, int *width, int *height)
{
   IMAGO_BEGIN;
   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   Image &img = context->img;
   unsigned char *buf = new unsigned char[img.getWidth() * img.getHeight()];

   *height = img.getHeight();
   *width = img.getWidth();

   for (int j = 0; j != img.getHeight(); j++)
   {
      int offset = j * img.getWidth();

      for (int i = 0; i != img.getWidth(); i++)
      {
         buf[offset + i] = img.getByte(i, j);
      }
   }

   *data = buf;
   IMAGO_END;
}

CEXPORT int imagoSaveImageToFile( const char *filename )
{
   IMAGO_BEGIN;
   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   if (context->img.isInit())
   {
      ImageUtils::saveImageToFile(context->img, filename);
   }

   IMAGO_END;
}

CEXPORT int imagoRecognize(int* warningsCountDataOut)
{
   IMAGO_BEGIN;

   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   ChemicalStructureRecognizer &csr = getRecognizer();

   csr.setImage(context->img);
   csr.recognize(context->vars, context->mol);
   if (warningsCountDataOut)
   {
	   (*warningsCountDataOut) = context->mol.getWarningsCount() + context->mol.getDissolvingsCount() / context->vars.main.DissolvingsFactor;
   }
   context->molfile = expandSuperatoms(context->vars, context->mol);

   IMAGO_END;
}

CEXPORT int imagoSaveMolToFile( const char *FileName )
{
   IMAGO_BEGIN;

   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   
   {
	   FileOutput fout(FileName);
	   fout.writeString(context->molfile);
   }

   IMAGO_END;
}

CEXPORT int imagoSaveMolToBuffer( char **buf, int *buf_size )
{
   IMAGO_BEGIN;

   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   std::string &out_buf = context->molfile;
   
   *buf = new char[out_buf.size()];
   memcpy(*buf, out_buf.c_str(), out_buf.size());
   *buf_size = out_buf.size();
   (*buf)[out_buf.size() - 1] = 0;

   IMAGO_END;
}

CEXPORT int imagoSetLogging(bool enable)
{
   IMAGO_BEGIN;

   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   context->vars.general.LogEnabled = enable;
   // warning: this is not thread-sensitive setter:
   imago::getLogExt().setLoggingEnabled(enable);

   IMAGO_END;
}

CEXPORT int imagoSetSessionSpecificData( void *data )
{
   IMAGO_BEGIN;

   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   context->session_specific_data = data;

   IMAGO_END;
}

CEXPORT int imagoGetSessionSpecificData( void **data )
{
   IMAGO_BEGIN;

   if (data != 0)
   {
      RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
      *data = context->session_specific_data;
   }

   IMAGO_END;
}

CEXPORT const char* imagoGetLastError()
{
   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   std::string &error_buf = context->error_buf;

   return error_buf.c_str();
}
