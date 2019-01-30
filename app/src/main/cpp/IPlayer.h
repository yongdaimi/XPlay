//
// Created by xp.chen on 2019/01/07.
//

#ifndef XPLAY_IPLAYER_H
#define XPLAY_IPLAYER_H


#include "XThread.h"
#include "XParameters.h"

class IDumex;
class IDecoder;
class IResample;
class IVideoView;
class IAudioPlayer;

class IPlayer : public XThread{

public:
    static IPlayer* Get(unsigned char index = 0);
    virtual bool Open(const char *path);
    virtual bool Start();
    virtual void InitView(void *win);

    /** 音频输出参数配置 */
    XParameters outParams;
    bool isEnableHardDecoder = true;
    IDumex *demux = 0;
    IDecoder *vDecoder = 0;
    IDecoder *aDecoder = 0;
    IResample *resample = 0;
    IVideoView *videoView = 0;
    IAudioPlayer *audioPlayer = 0;

protected:
    IPlayer(){};

};


#endif //XPLAY_IPLAYER_H
