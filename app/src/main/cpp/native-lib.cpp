#include <jni.h>
#include <string>
#include "IDumex.h"
#include "FFDumex.h"
#include "XLog.h"

static const char *url = "/sdcard/v1080.mp4";

extern "C" JNIEXPORT jstring JNICALL
Java_com_yuneec_android_xplay_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";


    IDumex *de = new FFDumex();
    bool openFlag = de->Open(url);
    if (!openFlag) return env->NewStringUTF(hello.c_str());
    de->Start();

    XSleep(3000);

    de->Stop();

    return env->NewStringUTF(hello.c_str());
}
