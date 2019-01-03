//
// Created by xp.chen on 2018/12/27.
//

#include "FFResample.h"
#include "XLog.h"

extern "C" {
#include <libswresample/swresample.h>
#include <libavcodec/avcodec.h>
}


bool FFResample::Open(XParameters in, XParameters out)
{
    //音频重采样上下文初始化
    actx = swr_alloc();
    actx = swr_alloc_set_opts(actx,
                              av_get_default_channel_layout(out.channels),
                              AV_SAMPLE_FMT_S16, out.sample_rate,
                              av_get_default_channel_layout(in.params->channels),
                              (AVSampleFormat)in.params->format,in.params->sample_rate,
                              0,0 );

    int re = swr_init(actx);
    if(re != 0) {
        XLOGE("FFResample:: swr_init() failed!");
        return false;
    } else {
        XLOGI("FFResample:: swr_init() success!");
    }
    outChannels = in.params->channels;
    outFormat = AV_SAMPLE_FMT_S16;
    return true;
}



XData FFResample::Resample(XData inData)
{
    // 执行具体的重采样
    // 输出空间的分配
    if (inData.size <= 0 || !inData.data) return XData();
    if (!actx) return XData();
    AVFrame *frame = (AVFrame *)inData.data;
    XData out;
    // 通道数 * 单通道样本数 * 样本字节大小
    int outSize = outChannels * frame->nb_samples * av_get_bytes_per_sample((AVSampleFormat)outFormat);
    if (outSize <= 0) return XData();
    // XLOGI("FFResample:: outsize data size is: %d", outSize);

    out.Alloc(outSize);
    uint8_t *outArr[2] = {0};
    outArr[0] = out.data;
    int len = swr_convert(actx, outArr, frame->nb_samples, (const uint8_t **)frame->data, frame->nb_samples);
    if (len <= 0) {
        XLOGE("FFResample:: swr_convert() failed");
        out.Drop();
        return XData();
    }
    // XLOGI("FFResample:: swr_convert() success = %d", len);
    return out;
}



