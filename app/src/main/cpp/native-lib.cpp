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
#include "IAudioPlayer.h"
#include "SLAudioPlayer.h"
#include "IPlayer.h"
#include <android/native_window_jni.h>


static const char *path = "/sdcard/1080.mp4";

class TestObserver : public IObserver {
public:
    void Update(XData data) {
       // XLOGI("TestObserver update receive size is: %d", data.size);
    }

};

IVideoView *view  = NULL;

extern "C" JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *res)
{
    FFDecoder::initHard(vm);

    IDumex *de = new FFDumex();
    IDecoder *vDecoder = new FFDecoder();
    IDecoder *aDecoder = new FFDecoder();
    IResample *resample = new FFResample();
    view = new GLVideoView();
    IAudioPlayer *audioPlayer = new SLAudioPlayer();

    de->AddObserver(vDecoder);
    de->AddObserver(aDecoder);

    vDecoder->AddObserver(view);
    aDecoder->AddObserver(resample);

    resample->AddObserver(audioPlayer);

//    audioPlayer->StartPlay(outParams);

    /*de->Start();
    vDecoder->Start();
    aDecoder->Start();*/
    // XSleep(3000);
    // de->Stop();

    // 使用注入的形式设置类中的各项成员变量
    IPlayer::Get()->demux = de;
    IPlayer::Get()->vDecoder = vDecoder;
    IPlayer::Get()->aDecoder = aDecoder;
    IPlayer::Get()->resample = resample;
    IPlayer::Get()->videoView = view;
    IPlayer::Get()->audioPlayer = audioPlayer;
    IPlayer::Get()->Open(path);

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
    view->SetRender(win);
    // XEGL::Get()->Init(win);
    // XShader shader;
    // shader.Init();
}