//
// Created by xp.chen on 2019/01/07.
//

#include "IPlayer.h"
#include "IDumex.h"
#include "XLog.h"
#include "IDecoder.h"
#include "IResample.h"
#include "XParameters.h"
#include "IAudioPlayer.h"
#include "IVideoView.h"

IPlayer* IPlayer::Get(unsigned char index)
{
    static IPlayer p[256];
    return &p[index];
}


void IPlayer::Main()
{
    while (!isExit)
    {
        mux.lock();
        if (!audioPlayer || !vDecoder)
        {
            mux.unlock();
            XSleep(2);
            continue;
        }
        // 同步
        // 获取音频pts告诉视频
        int apts = audioPlayer->pts;
        // XLOGI("IPLayer:: apts = %d",apts);
        vDecoder->synPts = apts;
        mux.unlock();
        XSleep(2);
    }
}


bool IPlayer::Open(const char *path)
{

    mux.lock();
    /* 解封装器部分 */
    if (!demux || !demux->Open(path))
    {
        mux.unlock();
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
    if (outParams.sample_rate <= 0)
        outParams = demux->getAudioParams();
    if (!resample || !resample->Open(demux->getAudioParams(), outParams))
    {
        XLOGE("IPlayer:: resample open failed");
    }
    mux.unlock();
    return true;
}


bool IPlayer::Start()
{
    mux.lock();
    if (!demux || !demux->Start())
    {
        mux.unlock();
        XLOGE("IPlayer:: IPlayer Start() failed");
        return false;
    }
    if (aDecoder)
        aDecoder->Start();
    if (audioPlayer)
        audioPlayer->StartPlay(outParams);
    if (vDecoder)
        vDecoder->Start();
    XThread::Start();
    mux.unlock();
    return true;
}


void IPlayer::InitView(void *win)
{
    if (videoView)
        videoView->SetRender(win);
}






