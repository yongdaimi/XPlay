#include <jni.h>
#include <string>
#include "IDumex.h"
#include "FFDumex.h"
#include "XLog.h"
#include "IDecoder.h"
#include "FFDecoder.h"
#include "XEGL.h"
#include "XShader.h"
#include "IVideoView.h"
#include "GLVideoView.h"
#include "IResample.h"
#include "FFResample.h"
#include <android/native_window_jni.h>


static const char *url = "/sdcard/v1080.mp4";


class TestObserver : public IObserver {
public:
    void Update(XData data) {
       // XLOGI("TestObserver update receive size is: %d", data.size);
    }

};

IVideoView *view  = NULL;

extern "C" JNIEXPORT jstring JNICALL
Java_com_yuneec_android_xplay_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    IDumex *de = new FFDumex();
    bool openFlag = de->Open(url);
    if (!openFlag) return env->NewStringUTF(hello.c_str());
    // TestObserver *testObj = new TestObserver();
    // de->AddObserver(testObj);

    IDecoder *vDecoder = new FFDecoder();
    vDecoder->Open(de->getVideoParams());

    IDecoder *aDecoder = new FFDecoder();
    aDecoder->Open(de->getAudioParams());

    de->AddObserver(vDecoder);
    de->AddObserver(aDecoder);

    view = new GLVideoView();
    vDecoder->AddObserver(view);

    IResample *resample = new FFResample();
    aDecoder->AddObserver(resample);
    resample->Open(de->getAudioParams());

    de->Start();
    vDecoder->Start();
    aDecoder->Start();

    // XSleep(3000);
    // de->Stop();

    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_yuneec_android_xplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    view->SetRender(win);
    // XEGL::Get()->Init(win);
    // XShader shader;
    // shader.Init();
}