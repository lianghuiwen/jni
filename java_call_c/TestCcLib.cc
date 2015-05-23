#include "TestCcLib.h"
#include <stdlib.h>
#include <string.h>

// jstring to char*
char* jstringToString(JNIEnv* env, jstring jstr)
{        
    char* rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0)
    {
        rtn = (char*)malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

// char* to jstring
jstring stringToJstring(JNIEnv* env, const char* str)
{
    jstring encoding = env->NewStringUTF("gbk");
    jclass strClass = env->FindClass("Ljava/lang/String;");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(strlen(str));
    env->SetByteArrayRegion(bytes, 0, strlen(str), (jbyte*)str);
    return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
}

JNIEXPORT jstring JNICALL Java_TestCcLib_callC(JNIEnv* env, jclass jc, jstring str)
{
    printf("C++: %s\n", jstringToString(env, str));
    const char* cppStr = "c++_string";
    return stringToJstring(env, cppStr);
}