//
// Created by xp.chen on 2019/01/07.
//

#include "IPlayer.h"
#include "IDumex.h"
#include "XLog.h"
#include "IDecoder.h"
#include "IResample.h"
#include "XParameters.h"

IPlayer* IPlayer::Get(unsigned char index)
{
    static IPlayer p[256];
    return &p[index];
}

bool IPlayer::Open(const char *path)
{

    /* 解封装器部分 */
    if (!demux || !demux->Open(path))
    {
        XLOGE("IPlayer:: IDemux open failed: %s", path);
        return false;
    }

    /* 解码器部分 解封装后的数据有可能是原始数据，可以直接用来播放，则不需要解码*/
    // 视频
    if (!vDecoder || !vDecoder->Open(demux->getVideoParams(), isEnableHardDecoder))
    {
        XLOGE("IPlayer:: vDecoder open failed");
    }

    // 音频
    if (!aDecoder || !aDecoder->Open(demux->getAudioParams()))
    {
        XLOGE("IPlayer:: aDecoder open failed");
    }

    /* 重采样部分 这里的音频数据也有可能是可以直接用来播放的数据 */
    XParameters outParams = demux->getAudioParams();
    if (!resample || !resample->Open(demux->getAudioParams(), outParams))
    {
        XLOGE("IPlayer:: resample open failed");
    }


    return true;
}



bool IPlayer::Start()
{


    return true;
}




