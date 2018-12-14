#include <jni.h>
#include <string>
#include "IDumex.h"
#include "FFDumex.h"
#include "XLog.h"
#include "IDecoder.h"
#include "FFDecoder.h"

static const char *url = "/sdcard/v1080.mp4";


class TestObserver : public IObserver {
public:
    void Update(XData data) {
       // XLOGI("TestObserver update receive size is: %d", data.size);
    }

};


extern "C" JNIEXPORT jstring JNICALL
Java_com_yuneec_android_xplay_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    IDumex *de = new FFDumex();
    bool openFlag = de->Open(url);
    if (!openFlag) return env->NewStringUTF(hello.c_str());
    TestObserver *testObj = new TestObserver();
    de->AddObserver(testObj);

    IDecoder *vDecoder = new FFDecoder();
    vDecoder->Open(de->getVideoParams());

    de->Start();
    XSleep(3000);
    de->Stop();

    return env->NewStringUTF(hello.c_str());
}
