#include <jni.h>
#include <string>

#include "FFPlayerBuilder.h"
#include <android/native_window_jni.h>


static const char *path = "/sdcard/1080.mp4";
static IPlayer *player = NULL;

extern "C" JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *res)
{
    FFPlayerBuilder::InitHard(vm);
    player = FFPlayerBuilder::Get()->BuildPlayer();

    player->Open(path);
    player->Start();

    return JNI_VERSION_1_4;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_yuneec_android_xplay_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_yuneec_android_xplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    if (player)
        player->InitView(win);
}