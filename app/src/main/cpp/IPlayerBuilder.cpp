//
// Created by xp.chen on 2019/01/30.
//

#include "IPlayerBuilder.h"
#include "IDumex.h"
#include "IDecoder.h"
#include "IVideoView.h"
#include "IResample.h"
#include "IAudioPlayer.h"

IPlayer *IPlayerBuilder::BuildPlayer(unsigned char index)
{

    IPlayer *player = CreatePlayer(index);
    // 解封装器
    IDumex *dumex = CreateDemux();

    // 视频解码
    IDecoder *vdecoder = CreateDecoder();

    // 音频解码
    IDecoder *adecoder = CreateDecoder();

    // 添加观察者
    dumex->AddObserver(vdecoder);
    dumex->AddObserver(adecoder);

    // VideoView
    IVideoView *videoView = CreateVideoView();
    vdecoder->AddObserver(videoView);

    // 音频重采样
    IResample *resample = CreateResample();
    adecoder->AddObserver(resample);

    // 音频播放器
    IAudioPlayer *audioPlayer = CreateAudioPlayer();
    resample->AddObserver(audioPlayer);

    // 构建播放器
    player->demux = dumex;
    player->vDecoder = vdecoder;
    player->aDecoder = adecoder;
    player->videoView = videoView;
    player->resample = resample;
    player->audioPlayer = audioPlayer;

    return player;
}
