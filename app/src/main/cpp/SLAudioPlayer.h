//
// Created by xp.chen on 2018/12/28.
//

#ifndef XPLAY_SLAUDIOPLAYER_H
#define XPLAY_SLAUDIOPLAYER_H


#include "IAudioPlayer.h"

class SLAudioPlayer : public IAudioPlayer{
public:
    virtual bool StartPlay(XParameters out);
    void PlayCall(void *bufq);
    SLAudioPlayer();
    virtual ~SLAudioPlayer();

protected:
    unsigned char *buf = 0;
};


#endif //XPLAY_SLAUDIOPLAYER_H
