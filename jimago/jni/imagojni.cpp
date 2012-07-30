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

#include "jni.h"
#include "imago_c.h"

#define JNINAME(name) JNICALL Java_com_gga_Imago_##name

#define JNICEXPORT extern "C" JNIEXPORT

static void throwException( JNIEnv *env, const char *exc_class, const char *message )
{
   jclass cls = env->FindClass(exc_class);

   if (cls == NULL)
      return;

   env->ThrowNew(cls, message);
   env->DeleteLocalRef(cls);
}

static void throwImagoException (JNIEnv *env)
{
   throwException(env, "java/lang/Exception", imagoGetLastError());
}

static void setSession( JNIEnv *env, jobject obj )
{
   jclass cls = env->GetObjectClass(obj);
   jfieldID id = env->GetFieldID(cls, "_sid", "J");
   jlong sid = env->GetLongField(obj, id);
   imagoSetSessionId(sid);
}

struct LogData 
{
   JNIEnv *env;
   jobject thiz;
};

/*void javaLogPrinter( const char *str )
{
   LogData *data;
   imagoGetSessionSpecificData((void**)&data);

   if (data == 0)
   {
      fprintf(stderr, "javaLogPrinter: data is empty\n"); fflush(stdout);
      return;
   }
   JNIEnv *env = data->env;
   jobject thiz = data->thiz;
   
   jclass cls = env->GetObjectClass(thiz);
   jfieldID logCallbackId = env->GetFieldID(cls, "logCallback", "Lcom/gga/Imago$ImagoLogCallback;");

   if (logCallbackId == 0)
   {
      fprintf(stderr, "javaLogPrinter: ImagoLogCallback not found\n");
      return;
   }

   jobject logCallback = env->GetObjectField(thiz, logCallbackId);

   if (logCallback == 0)
      return;

   jclass logCallbackCls = env->GetObjectClass(logCallback);
   jmethodID mid = env->GetMethodID(logCallbackCls, "log", "(Ljava/lang/String;)V");

   if (mid == 0)
   {
      fprintf(stderr, "javaLogPrinter: ImagoLogCallback.log not found\n");
      return;
   }

   jstring jstr = env->NewStringUTF(str);
   env->CallObjectMethod(logCallback, mid, jstr);
}

JNICEXPORT void JNINAME(enableLog)( JNIEnv *env, jobject thiz )
{
   setSession(env, thiz);
   imagoSetLogPrinter(javaLogPrinter);
}

JNICEXPORT void JNINAME(disableLog)( JNIEnv *env, jobject thiz )
{
   setSession(env, thiz);
   imagoDisableLog();
}*/

JNICEXPORT jlong JNINAME(allocSessionId)( JNIEnv *env, jclass thiz )
{
   return imagoAllocSessionId();
}

JNICEXPORT void JNINAME(releaseSessionId)( JNIEnv *env, jclass clazz , jlong id)
{
   imagoReleaseSessionId(id);
}

JNICEXPORT jint JNINAME(getConfigsCount)( JNIEnv *env, jclass thiz )
{
   return imagoGetConfigsCount();
}

JNICEXPORT void JNINAME(setConfigNumber)( JNIEnv *env, jobject thiz, jint jnum)
{
   setSession(env, thiz);
   if (!imagoSetConfigNumber(jnum))
      throwImagoException(env);
}

JNICEXPORT void JNINAME(setFilter)( JNIEnv *env, jobject thiz, jstring jfilter)
{
   setSession(env, thiz);
   const char *filter = env->GetStringUTFChars(jfilter, 0);
   int ret = imagoSetFilter(filter);
   env->ReleaseStringUTFChars(jfilter, filter);
   if (!ret)
      throwImagoException(env);
}

JNICEXPORT void JNINAME(setBinarizationLevel)( JNIEnv *env, jobject thiz, jint jlevel)
{
//   setSession(env, thiz);
//   if (!imagoSetBinarizationLevel(jlevel))
//      throwImagoException(env);
}

JNICEXPORT void JNINAME(loadImageFromFile)( JNIEnv *env, jobject thiz, jstring jfilename)
{
   setSession(env, thiz);
   const char *filename = env->GetStringUTFChars(jfilename, 0);
   int ret = imagoLoadImageFromFile(filename);
   env->ReleaseStringUTFChars(jfilename, filename);
   if (!ret)
      throwImagoException(env);
}

JNICEXPORT void JNINAME(loadGreyscaleRawImage)( JNIEnv *env, jobject thiz, jbyteArray jbuffer, jint w, jint h )
{
   setSession(env, thiz);
   //int len = env->GetArrayLength(jbuffer);
   void *buffer = env->GetPrimitiveArrayCritical(jbuffer, 0);
   int ret = imagoLoadGreyscaleRawImage((const char *)buffer, w, h);
   env->ReleasePrimitiveArrayCritical(jbuffer, buffer, 0);
   if (!ret)
      throwImagoException(env);
}

JNICEXPORT void JNINAME(loadImageFromBuffer)( JNIEnv *env, jobject thiz, jbyteArray jbuffer)
{
   setSession(env, thiz);
   int len = env->GetArrayLength(jbuffer);
   void *buffer = env->GetPrimitiveArrayCritical(jbuffer, 0);
   int ret = imagoLoadImageFromBuffer((const char*)buffer, len);
   env->ReleasePrimitiveArrayCritical(jbuffer, buffer, 0);
   if (!ret)
      throwImagoException(env);
}

JNICEXPORT void JNINAME(saveImageToFile)( JNIEnv *env, jobject thiz, jstring jfilename)
{
   setSession(env, thiz);
   const char *filename = env->GetStringUTFChars(jfilename, 0);
   int ret = imagoSaveImageToFile(filename);
   env->ReleaseStringUTFChars(jfilename, filename);
   if (!ret)
      throwImagoException(env);   
}

JNICEXPORT void JNINAME(recognize)( JNIEnv *env, jobject thiz )
{
   setSession(env, thiz);
   LogData data;
   data.env = env;
   data.thiz = thiz;
   imagoSetSessionSpecificData(&data);
   int warningsCount = 0;
   int ret = imagoRecognize(&warningsCount);
   imagoSetSessionSpecificData(0);
   if (!ret)
      throwException(env, "com/gga/Imago$NoResultException", imagoGetLastError());
}

JNICEXPORT void JNINAME(saveMolToFile)( JNIEnv *env, jobject thiz, jstring jfilename)
{
   setSession(env, thiz);
   const char *filename = env->GetStringUTFChars(jfilename, 0);
   int ret = imagoSaveMolToFile(filename);
   env->ReleaseStringUTFChars(jfilename, filename);
   if (!ret)
      throwImagoException(env);
}

JNICEXPORT jstring JNINAME(getResult)( JNIEnv *env, jobject thiz )
{
   setSession(env, thiz);
   char *buf;
   int size;
   if (!imagoSaveMolToBuffer(&buf, &size))
      throwImagoException(env);
   jstring mol = env->NewStringUTF(buf);
   return mol;
}

JNICEXPORT void JNINAME(loadAndFilterImageFile) ( JNIEnv *env, jobject thiz, jstring jfilename)
{
   setSession(env, thiz);
   const char *filename = env->GetStringUTFChars(jfilename, 0);
   LogData data;
   data.env = env;
   data.thiz = thiz;
   imagoSetSessionSpecificData(&data);
   int ret = imagoLoadImageFromFile(filename);
   imagoFilterImage();
   imagoSetSessionSpecificData(0);
   env->ReleaseStringUTFChars(jfilename, filename);
   if (!ret)
      throwImagoException(env);
}

JNICEXPORT jint JNINAME(getPrefilteredImageWidth)( JNIEnv *env, jobject thiz )
{
   setSession(env, thiz);
   int w, h;
   if (!imagoGetPrefilteredImageSize(&w, &h))
      throwImagoException(env);
   return w;
}

JNICEXPORT jint JNINAME(getPrefilteredImageHeight)( JNIEnv *env, jobject thiz )
{
   setSession(env, thiz);
   int w, h;
   if (!imagoGetPrefilteredImageSize(&w, &h))
      throwImagoException(env);
   return h;
}

JNICEXPORT jbyteArray JNINAME(getPrefilteredImage)( JNIEnv *env, jobject thiz )
{
   setSession(env, thiz);
   unsigned char *buf;
   int w, h;
   if (!imagoGetPrefilteredImage(&buf, &w, &h))
      throwImagoException(env);
   jbyteArray jbuf = env->NewByteArray(w * h);
   env->SetByteArrayRegion(jbuf, 0, w * h, (jbyte *)buf);
   //free(buf);
   return jbuf;
}
