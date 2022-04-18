/****************************************************************************
* Copyright (C) from 2009 to Present EPAM Systems.
*
* This file is part of Imago toolkit.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
***************************************************************************/

#pragma once

/* All functions return 0 on error, and a nonzero value on success */

/* Imago library acts as a state machine.
 * You can use multiple Imago instances simultaneously, using the
 * 'session ID-s' (see below). It is obligatory to allocate at least one
 * instance to get Imago library work properly.
 */

/* Get the version of Imago.*/
CEXPORT const char *imagoGetVersion();

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

/* Set the ID of the instance you are working with from current thread. */
CEXPORT void imagoSetSessionId( qword id );

/* Release a previously allocated instance. */
CEXPORT void imagoReleaseSessionId( qword id );

/* Set one of predefined configuration sets.
 * The given name should be selected from imagoGetConfigsList() results
 * Empty string as parameter means config auto-detection. */
CEXPORT int imagoSetConfig( const char *name );

/* Get the list of available predefined configuration sets separated by comma. */
CEXPORT const char* imagoGetConfigsList();

/* Choose the filter to process image before call imagoFilterImage()
 * name can be "prefilter_binarized", "prefilter_basic", or something else.
 * For the exact information see the filters_list.cpp file.
 * By default, filter from current config will be used. */
CEXPORT int imagoSetFilter( const char *name );

/* Image loading functions. */
CEXPORT int imagoLoadImageFromBuffer( const char *buf, const int buf_size );
CEXPORT int imagoLoadImageFromFile( const char *FileName );

/* PNG image saving function. */
CEXPORT int imagoSaveImageToFile( const char *FileName );

/* Load raw grayscale image - byte array of length width*height. */
CEXPORT int imagoLoadGreyscaleRawImage( const char *buf, const int width, const int height );

/* Enable or disable global log printing */
/* Modes are: 0 - disabled, 1 - enable log to file, 2 - enable log to virtual fs*/
/* WARNING: affects all threads/IDS */
CEXPORT int imagoSetLogging( int mode );

/* Attach some arbitrary data to the current Imago instance. */
CEXPORT int imagoSetSessionSpecificData( void *data );
CEXPORT int imagoGetSessionSpecificData( void **data );

/* Main recognition routine. Image must be loaded & filtered previously.
   Returns count of recognition warnings in warningsCountDataOut value (if specified) */
CEXPORT int imagoRecognize( int *warningsCountDataOut = NULL );

/* Molfile (.mol) output functions. */
CEXPORT int imagoSaveMolToBuffer( char **buf, int *buf_size );
CEXPORT int imagoSaveMolToFile( const char *fileName );
CEXPORT const char* imagoGetMol();

/* Process image filtering. */
CEXPORT int imagoFilterImage();

/* Returns filtered image ink percentage (0.0 .. 1.0) */
CEXPORT int imagoGetInkPercentage( double *result );

/* returns filtered image dimensions */
CEXPORT int imagoGetPrefilteredImageSize( int *width, int *height );

/* returns filtered image data */
CEXPORT int imagoGetPrefilteredImage( unsigned char **data, int *width, int *height );

/* returns count of files contained in log vfs. */
CEXPORT int imagoGetLogCount( int *count );

/* returns it's file name, length and content */
CEXPORT int imagoGetLogRecord( int it, char **filename, int *lengths, char **data );

/* clears all current vfs log content */
CEXPORT int imagoClearLog();
