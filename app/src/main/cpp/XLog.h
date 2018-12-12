//
// Created by xp.chen on 2018/11/26.
//

#ifndef XPLAY_XLOG_H
#define XPLAY_XLOG_H

#define LOG_TAG "xp.chen"

#ifdef ANDROID
#include <android/log.h>
#define XLOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define XLOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define XLOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#else
#define XLOGD(...) printf(LOG_TAG, __VA_ARGS__)
#define XLOGI(...) printf(LOG_TAG, __VA_ARGS__)
#define XLOGE(...) printf(LOG_TAG, __VA_ARGS__)
#endif

class XLog {

};


#endif //XPLAY_XLOG_H
