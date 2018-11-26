#include <jni.h>
#include <string>
#include "IDumex.h"
#include "FFDumex.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_yuneec_android_xplay_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    const char *url = "/sdcard/v10801.mp4";


    IDumex *de = new FFDumex();
    de->Open(url);

    return env->NewStringUTF(hello.c_str());
}
