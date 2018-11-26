//
// Created by xp.chen on 2018/11/26.
//

#include "FFDumex.h"
#include "XLog.h"

extern "C" {
#include "libavformat/avformat.h"
}

bool FFDumex::Open(const char *url)
{

    XLOGI("open file %s begin", url);
    int ret = avformat_open_input(&ic, url, 0, 0);
    if (ret != 0) {
        char buf[1024] = {0};
        av_strerror(ret, buf, sizeof(buf));
        XLOGE("FFDumex Open() failed. url is: %s, rea is: %s", url, buf);
        return false;
    }
    XLOGI("FFDumex Open %s success", url);

    // 读取文件信息
    ret = avformat_find_stream_info(ic, 0);
    if (ret != 0) {
        char buf[1024] = {0};
        av_strerror(ret, buf, sizeof(buf));
        XLOGE("FFDumex avformat_find_stream_info() failed. url is: %s, rea is: %s", url, buf);
        return false;
    }
    this->totalMs = ic->duration / (AV_TIME_BASE/1000);
    XLOGI("FFDumex total ms = %d", totalMs);

    return true;
}

XData FFDumex::Read()
{

    XData d;
    return d;
}

FFDumex::FFDumex()
{
    static bool isFirst = true;
    if (isFirst) {
        isFirst = false;
        // 注册所有解封装器
        av_register_all();
        // 注册解码器
        avcodec_register_all();
        // 初始化网络
        avformat_network_init();
        XLOGI("Register FFmpeg!");
    }
}



