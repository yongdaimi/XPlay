//
// Created by xp.chen on 2019/01/30.
//

#ifndef XPLAY_IPLAYERBUILDER_H
#define XPLAY_IPLAYERBUILDER_H

#include "IPlayer.h"

class IPlayerBuilder {

public:
    virtual IPlayer *BuildPlayer(unsigned char index = 0);

protected:
    virtual IDumex *CreateDemux() = 0;
    virtual IDecoder *CreateDecoder() = 0;
    virtual IResample *CreateResample() = 0;
    virtual IVideoView *CreateVideoView() = 0;
    virtual IAudioPlayer *CreateAudioPlayer() = 0;
    virtual IPlayer *CreatePlayer(unsigned char index) = 0;
};


#endif //XPLAY_IPLAYERBUILDER_H
