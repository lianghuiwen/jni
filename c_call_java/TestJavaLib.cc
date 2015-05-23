#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jni.h>

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

int main(int argc, char* argv[])
{
    // 创建JAVA虚拟机
    JavaVM* jvm = NULL;
    JNIEnv* env = NULL;
    JavaVMInitArgs args;
    JavaVMOption options[2];
    options[0].optionString = "-Djava.compiler=NONE";   // 禁用 JIT
    options[1].optionString = "-Djava.class.path=.";    // 用户类
    args.version = JNI_VERSION_1_2;
    args.nOptions = 2;
    args.options = options;
    args.ignoreUnrecognized = JNI_TRUE;
    long status = JNI_CreateJavaVM(&jvm, (void**)&env, &args);
    if (status != JNI_OK)
    {
        printf("JNI_CreateJavaVM error!\n");
        return -1;
    }

    // 获取当前线程的运行环境
    // JNIEnv* env_thread = NULL;
    // jvm->AttachCurrentThread((void**)&env_thread, NULL);

    // 获取类
    jclass cls = env->FindClass("TestJavaLib");
    if(cls == 0)
    {
        printf("FindClass error!\n");
        return -1;
    }

    // 创建类对象
    jmethodID mid = env->GetMethodID(cls,"<init>","()V");
    if(mid == 0)
    {
        printf("GetMethodID error!\n");
        return -1;
    }
    jobject obj = env->NewObject(cls, mid, 0);

    // 调用java方法
    jstring str = stringToJstring(env, "c++_string");
    mid = env->GetMethodID(cls, "callJava", "(Ljava/lang/String;)V");
    if(mid == 0)
    {  
        printf("GetMethodID error!\n");
        return -1;
    }
    env->CallVoidMethod(obj, mid, str);

    // 释放本线程使用的运行环境
    // jvm->DetachCurrentThread();

    // 销毁JAVA虚拟机
    jvm->DestroyJavaVM();
}
