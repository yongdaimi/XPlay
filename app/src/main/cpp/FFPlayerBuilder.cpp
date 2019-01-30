//
// Created by xp.chen on 2019/01/30.
//

#include "FFPlayerBuilder.h"

#include "FFDumex.h"
#include "FFDecoder.h"
#include "FFResample.h"
#include "GLVideoView.h"
#include "SLAudioPlayer.h"

IDumex *FFPlayerBuilder::CreateDemux()
{
    IDumex *ff = new FFDumex();
    return ff;
}

IDecoder *FFPlayerBuilder::CreateDecoder()
{
    IDecoder *ff = new FFDecoder();
    return ff;
}

IResample *FFPlayerBuilder::CreateResample()
{
    IResample *ff = new FFResample();
    return ff;
}

IVideoView *FFPlayerBuilder::CreateVideoView()
{
    IVideoView *gl = new GLVideoView();
    return gl;
}

IAudioPlayer *FFPlayerBuilder::CreateAudioPlayer()
{
    IAudioPlayer *ap = new SLAudioPlayer();
    return ap;
}

IPlayer *FFPlayerBuilder::CreatePlayer(unsigned char index)
{
    return IPlayer::Get(index);
}

void FFPlayerBuilder::InitHard(void *vm)
{
    return FFDecoder::initHard(vm);
}







