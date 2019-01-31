//
// Created by xp.chen on 2018/11/26.
//

#include "FFDumex.h"
#include "XLog.h"

extern "C" {
#include "libavformat/avformat.h"
}

//分数转为浮点数
static double r2d(AVRational r)
{
    return r.num == 0 || r.den == 0 ?0.:(double) r.num/(double)r.den;
}

bool FFDumex::Open(const char *url)
{
    XLOGI("open file %s begin", url);
    Close();
    mux.lock();
    int ret = avformat_open_input(&ic, url, 0, 0);
    if (ret != 0) {
        char buf[1024] = {0};
        av_strerror(ret, buf, sizeof(buf));
        mux.unlock();
        XLOGE("FFDumex::Open() failed. url is: %s, rea is: %s", url, buf);
        return false;
    }
    XLOGI("FFDumex open %s success", url);

    // 读取文件信息
    ret = avformat_find_stream_info(ic, 0);
    if (ret != 0) {
        char buf[1024] = {0};
        av_strerror(ret, buf, sizeof(buf));
        mux.unlock();
        XLOGE("FFDumex::avformat_find_stream_info() failed. url is: %s, rea is: %s", url, buf);
        return false;
    }
    this->totalMs = ic->duration / (AV_TIME_BASE/1000);
    XLOGI("FFDumex total ms = %d", totalMs);
    mux.unlock();
    getVideoParams();
    getAudioParams();
    return true;
}

void FFDumex::Close()
{
    mux.lock();
    if (ic)
        avformat_close_input(&ic);
    mux.unlock();
}



XData FFDumex::Read()
{
    mux.lock();
    if (!ic) {
        mux.unlock();
        return XData();
    }
    XData d;
    AVPacket *pkt = av_packet_alloc();
    int ret = av_read_frame(ic, pkt);
    if (ret != 0) {
        av_packet_free(&pkt);
        mux.unlock();
        return XData();
    }
    // XLOGI("pkt size: %d, pts is: %lld", pkt->size, pkt->pts);
    d.data = (unsigned char *)pkt;
    d.size = pkt->size;
    if (pkt->stream_index == audioStreamIndex) {
        d.isAudio = true;
    } else if (pkt->stream_index == videoStreamIndex) {
        d.isAudio = false;
    } else {
        av_packet_free(&pkt);
        mux.unlock();
        return XData();
    }

    //转换pts
    pkt->pts = pkt->pts * (1000*r2d(ic->streams[pkt->stream_index]->time_base));
    pkt->dts = pkt->dts * (1000*r2d(ic->streams[pkt->stream_index]->time_base));
    d.pts = (int)pkt->pts;
    mux.unlock();

    //XLOGE("demux pts %d",d.pts);
    return d;
}


XParameters FFDumex::getVideoParams()
{
    mux.lock();
    if (!ic) {
        mux.unlock();
        XLOGE("FFDumex:: getVideoParams() failed, ic is null");
        return XParameters();
    }
    // 查找视频流对象索引
    int videoIndex = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
    if (videoIndex < 0) {
        mux.unlock();
        XLOGE("FFDumex:: getVideoParams() failed, av_find_best_stream() failed");
        return XParameters();
    }
    videoStreamIndex = videoIndex;
    XParameters videoParams;
    videoParams.params = ic->streams[videoIndex]->codecpar;
    mux.unlock();
    return videoParams;
}

XParameters FFDumex::getAudioParams()
{
    mux.lock();
    if (!ic) {
        mux.unlock();
        XLOGE("FFDumex:: getAudioParams() failed, ic is null");
        return XParameters();
    }
    // 查找音频流对象索引
    int audioIndex = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, 0, 0);
    if (audioIndex < 0) {
        mux.unlock();
        XLOGE("FFDumex:: getAudioParams() failed, av_find_best_stream() failed");
        return XParameters();
    }
    audioStreamIndex = audioIndex;
    XParameters audioParams;
    audioParams.params = ic->streams[audioIndex]->codecpar;
    audioParams.channels = ic->streams[audioIndex]->codecpar->channels;
    audioParams.sample_rate = ic->streams[audioIndex]->codecpar->sample_rate;
    mux.unlock();
    return audioParams;
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



