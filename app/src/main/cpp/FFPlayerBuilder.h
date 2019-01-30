//
// Created by xp.chen on 2019/01/30.
//

#ifndef XPLAY_FFPLAYERBUILDER_H
#define XPLAY_FFPLAYERBUILDER_H


#include "IPlayerBuilder.h"

class FFPlayerBuilder : public IPlayerBuilder{

public:
    static FFPlayerBuilder *Get()
    {
        static FFPlayerBuilder ff;
        return &ff;
    }

public:
    static void InitHard(void *vm);

protected:
    FFPlayerBuilder(){};
    virtual IDumex *CreateDemux();
    virtual IDecoder *CreateDecoder();
    virtual IResample *CreateResample();
    virtual IVideoView *CreateVideoView();
    virtual IAudioPlayer *CreateAudioPlayer();
    virtual IPlayer *CreatePlayer(unsigned char index);

};


#endif //XPLAY_FFPLAYERBUILDER_H
