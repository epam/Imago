#ifndef _ismiles_c_h
#define _ismiles_c_h

#ifdef _WIN32

#define DLLEXPORT __declspec(dllexport)

#else

#define DLLEXPORT

#endif /* _WIN32 */

#ifndef __cplusplus
#define CEXPORT DLLEXPORT
#else
#define CEXPORT extern "C" DLLEXPORT
#endif

/* Load JPG image & process it (rotate, filter) using iSMILES 
 * !Careful! memory leak possible */
CEXPORT char *loadAndProcessJPGImage( const char *filename, int *width, int *height );


#endif /* _ismiles_c_h */
