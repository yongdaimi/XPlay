//
// Created by xp.chen on 2018/12/14.
//


#include "FFDecoder.h"
#include "XLog.h"

extern "C" {
#include <libavcodec/avcodec.h>
}

bool FFDecoder::Open(XParameters params)
{
    if (!params.params) return false;
    AVCodecParameters *codecParams = params.params;
    // 1.查找解码器
    AVCodec *codec = avcodec_find_decoder(codecParams->codec_id);
    if (!codec) {
        XLOGE("FFDecoder:: find decoder failed");
        return false;
    }
    XLOGI("FFDecoder:: find decoder success");
    // 2. 创建解码器上下文并复制参数
    avctx = avcodec_alloc_context3(codec);
    avctx->thread_count = 8; // 设置允许多线程解码
    avcodec_parameters_to_context(avctx, codecParams);
    // 3. 打开解码器
    int ret = avcodec_open2(avctx, 0, 0);
    if (ret != 0) {
        char buf[1024] = {0};
        av_strerror(ret, buf, sizeof(buf));
        XLOGE("FFDecoder:: open codec failed, %s", buf);
        return false;
    }
    XLOGI("FFDecoder:: open codec success");

    return true;
}

bool FFDecoder::SendPacket(XData pkt)
{
    if (!pkt.size || !pkt.data) {
        XLOGE("FFDecoder:: SendPacket() failed, pkt is null ");
        return false;
    }
    if (!avctx) {
        XLOGE("FFDecoder:: SendPacket() failed, avctx is null ");
        return false;
    }
    int ret = avcodec_send_packet(avctx, (AVPacket *)pkt.data);
    if (ret != 0) {
        XLOGE("FFDecoder:: SendPacket() failed, send pkt failed ");
        return false;
    }
    return true;
}


XData FFDecoder::RecvFrame()
{
    if (!avctx) {
        XLOGE("FFDecoder:: RecvFrame() failed, avctx is null ");
        return XData();
    }

    if (!frame) {
        frame = av_frame_alloc();
    }
    int ret = avcodec_receive_frame(avctx, frame);
    if (ret != 0) {
        XLOGE("FFDecoder:: RecvFrame() failed, avcodec_receive_frame() failed ");
        return XData();
    }
    XData d;
    d.data = (unsigned char *)frame;
    if (avctx->codec_type == AVMEDIA_TYPE_VIDEO) {
        d.size = (frame->linesize[0] + frame->linesize[1] + frame->linesize[2]) * frame->height;
    }
    XLOGI("FFDecoder:: RecvFrame() decoder success");
    return d;
}






