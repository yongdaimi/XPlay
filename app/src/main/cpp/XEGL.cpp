//
// Created by xp.chen on 2018/12/25.
//

#include "XEGL.h"
#include "XLog.h"
#include <android/native_window_jni.h>
#include <EGL/egl.h>


class CXEGL : public XEGL
{
public:
    EGLDisplay display = EGL_NO_DISPLAY;
    EGLSurface surface = EGL_NO_SURFACE;
    EGLContext context = EGL_NO_CONTEXT;

    virtual bool Init(void *win) {
        // 初始化EGL
        ANativeWindow *nwin = (ANativeWindow*)win;
        // 1. 获取EGLDisplay对象
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (display == EGL_NO_DISPLAY) {
            XLOGE("XEGL:: eglGetDisplay() failed");
            return false;
        }
        XLOGI("XEGL:: eglGetDisplay() success");
        // 2. 初始化Display
        if (EGL_TRUE != eglInitialize(display, 0, 0)) {
            XLOGE("XEGL:: eglInitialize() failed");
            return false;
        }
        XLOGI("XEGL:: eglInitialize() success");
        // 3. 创建并配置surface
        EGLint configSpec[] = {
                EGL_RED_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_BLUE_SIZE, 8,
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_NONE
        };
        EGLConfig config = 0; // 获取到的配置项
        EGLint numConfigs = 0;
        if (EGL_TRUE != eglChooseConfig(display, configSpec, &config, 1, &numConfigs)) {
            XLOGE("XEGL:: eglChooseConfig() failed");
            return false;
        }
        XLOGI("XEGL:: eglChooseConfig() success");
        surface = eglCreateWindowSurface(display, config, nwin, NULL);
        // 4. 创建并打开EGL上下文
        const EGLint ctxAttr[] = {
                EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
        };
        context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxAttr);
        if (context == EGL_NO_CONTEXT) {
            XLOGE("XEGL:: eglCreateContext() failed");
            return false;
        }
        XLOGI("XEGL:: eglCreateContext() success");
        if (EGL_TRUE != eglMakeCurrent(display, surface, surface, context)) {
            XLOGE("XEGL:: eglMakeCurrent() failed");
            return false;
        }
        XLOGI("XEGL:: eglMakeCurrent() success");
        return true;
    }

};

XEGL *XEGL::Get()
{
    static CXEGL egl;
    return &egl;
}



