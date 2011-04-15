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

#ifndef _imago_c_h
#define _imago_c_h

#ifdef _WIN32

#define DLLEXPORT __declspec(dllexport)
#define qword unsigned _int64

#else 

#define DLLEXPORT
#define qword unsigned long long

#endif /* _WIN32 */

#ifndef __cplusplus
#define CEXPORT DLLEXPORT
#else
#define CEXPORT extern "C" DLLEXPORT
#endif

/* All functions return 0 on error, and a nonzero value on success */

/* Imago library acts as a state machine.
 * You can use multiple Imago instances simultaneously, using the
 * 'session ID-s' (see below). It is obligatory to allocate at least one
 * instance to get Imago library work properly.
 */

/* Get the last error message.
 * This can be called if some other function returned zero value.
 */
CEXPORT const char *imagoGetLastError();

/* Allocate an instance. All instances are independent, that is,
 * they have separate images, configurations settings, resulting
 * molfiles, and error messages.
 * Using Imago library without allocation an instance will cause an error.
 */
CEXPORT qword imagoAllocSessionId();

/* Set the ID of the instance you are working with from current thread */
CEXPORT void imagoSetSessionId( qword id );

/* Release a previously allocated instance */
CEXPORT void imagoReleaseSessionId( qword id );

/* Set one of predefined configuration sets.
 * The given number must be nonnegative and less than the number of
 * available configuration sets. By default, the number is 0.
 */
CEXPORT int imagoSetConfigNumber( const int number );

/* Get the number of available predefined configuration sets. */
CEXPORT int imagoGetConfigsCount();

/* Choose filter to process image before recognition. 
 * name can be "sharp" or "blur".
 * By default, filter from current config will be used.
 */
CEXPORT int imagoSetFilter( const char *name );

/* Manually choose binarization level for image.
 * level can be between 0 and 255.
 * If the pixel color is less than the given level, it is considered black.
 * Otherwise, white. By default, the level from the current configuration set
 * will be used.
 */
CEXPORT int imagoSetBinarizationLevel( const int level );

/* Image loading functions. */
CEXPORT int imagoLoadPngImageFromBuffer( const char *buf, const int buf_size );
CEXPORT int imagoLoadPngImageFromFile( const char *FileName );
CEXPORT int imagoLoadJpgImageFromFile( const char *FileName );

/* PNG image saving function. */
CEXPORT int imagoSavePngImageToFile( const char *FileName );

/* Load raw grayscale image - byte array of length width*height. */
CEXPORT int imagoLoadGreyscaleRawImage( const char *buf, const int width, const int height );

/* Set the callback function for log printing. 
 * By default, log is printed to the standard output.
 */
CEXPORT int imagoSetLogPrinter( void (*printer)( const char *str ) );

/* Disable log printing (set quiet mode). */
CEXPORT int imagoDisableLog();

CEXPORT int imagoResetLog();

/* Attach some arbitrary data to the current Imago instance. */
CEXPORT int imagoSetSessionSpecificData( void *data );
CEXPORT int imagoGetSessionSpecificData( void **data );

/* Main recognition routine. 
 * Image must be loaded previously. */
CEXPORT int imagoRecognize();

/* Molfile (.mol) output functions. */
CEXPORT int imagoSaveMolToBuffer( char **buf, int *buf_size );
CEXPORT int imagoSaveMolToFile( const char *FileName );

CEXPORT int imagoFilterImage();

CEXPORT int imagoGetPrefilteredImageSize (int *width, int *height);
CEXPORT int imagoGetPrefilteredImage (unsigned char **data, int *width, int *height);

#endif /* _imago_c_h */
