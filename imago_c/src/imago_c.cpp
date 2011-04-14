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
#include "image_utils.h"
#include "molfile_saver.h"
#include "log.h"
#include "exception.h"
#include "output.h"
#include "scanner.h"
#include "comdef.h"
#include "recognition_settings.h"
#include "session_manager.h"
#include "png_loader.h"
#include "current_session.h"

#define IMAGO_BEGIN try {                                                    

#define IMAGO_END   } catch ( Exception &e )                                 \
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
   void prefilterFile (const char *filename, Image &img, const CharacterRecognizer &cr );
}

using namespace imago;

struct RecognitionContext
{
   Image img;
   Molecule mol;
   std::string out_buf;
   std::string error_buf;
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
   RecognitionContext *&context = (RecognitionContext *&)gSession.get()->context(); 
   
   if (context == 0)
      context = new RecognitionContext();
}

CEXPORT void imagoReleaseSessionId( qword id )
{
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
   return RecognitionSettings::CONF_COUNT;
}

CEXPORT int imagoSetConfigNumber( const int number )
{
   IMAGO_BEGIN;

   getSettings().initConfig(number);

   IMAGO_END;
}

CEXPORT int imagoSetFilter( const char *Name )
{
   IMAGO_BEGIN;

   getSettings().set("Filter", Name);

   IMAGO_END;
}

CEXPORT int imagoSetBinarizationLevel( const int Level )
{
   IMAGO_BEGIN;

   getSettings().set("BinarizationLevel", Level);

   IMAGO_END;
}

CEXPORT int imagoLoadPngImageFromFile( const char *FileName )
{
   IMAGO_BEGIN;
   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   ImageUtils::loadImageFromFile(context->img, FileName);
      
   IMAGO_END;
}

CEXPORT int imagoLoadPngImageFromBuffer( const char *buf, const int buf_size )
{
   IMAGO_BEGIN;
   
   //TODO:
   /*
   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   std::string in_buf(buf, buf_size);
   BufferScanner scan(in_buf);

   PngLoader loader(scan);
   loader.loadImage(context->img);
   */

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

CEXPORT int imagoLoadAndFilterJpgFile( const char *filename )
{
   IMAGO_BEGIN;
   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   Image &img = context->img;

   img.clear();
   prefilterFile(filename, img, getRecognizer().getCharacterRecognizer());
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

CEXPORT int imagoSavePngImageToFile( const char *filename )
{
   IMAGO_BEGIN;
   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   if (context->img.isInit())
   {
      ImageUtils::saveImageToFile(context->img, filename);
   }

   IMAGO_END;
}

CEXPORT int imagoRecognize()
{
   IMAGO_BEGIN;

   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   ChemicalStructureRecognizer &csr = getRecognizer();

   csr.setImage(context->img);
   csr.recognize(context->mol);

   IMAGO_END;
}

CEXPORT int imagoSaveMolToFile( const char *FileName )
{
   IMAGO_BEGIN;

   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   FileOutput fout(FileName);
   MolfileSaver saver(fout);

   saver.saveMolecule(context->mol);

   IMAGO_END;
}

CEXPORT int imagoSaveMolToBuffer( char **buf, int *buf_size )
{
   IMAGO_BEGIN;

   RecognitionContext *context = (RecognitionContext*)gSession.get()->context();
   std::string &out_buf = context->out_buf;
   ArrayOutput aout(out_buf);
   MolfileSaver saver(aout);

   saver.saveMolecule(context->mol);

   //Is that correct?
   *buf = new char[out_buf.size()];
   memcpy(*buf, out_buf.c_str(), out_buf.size());
   *buf_size = out_buf.size();
   (*buf)[out_buf.size() - 1] = 0;

   IMAGO_END;
}

CEXPORT int imagoSetLogPrinter( void (*printer)( const char *str ) )
{
   IMAGO_BEGIN;

   getLog().setPrinter(printer);

   IMAGO_END;
}

CEXPORT int imagoDisableLog()
{
   IMAGO_BEGIN;

   getLog().setPrinter(0);

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
