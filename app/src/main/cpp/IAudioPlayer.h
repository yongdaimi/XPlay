//
// Created by xp.chen on 2018/12/28.
//

#ifndef XPLAY_IAUDIOPLAYER_H
#define XPLAY_IAUDIOPLAYER_H


#include "IObserver.h"
#include "XParameters.h"

class IAudioPlayer : public IObserver{
public:
    /** 接收重采样(IResample)过来的数据 */
    virtual void Update(XData data);
    virtual bool StartPlay(XParameters params) = 0;
};


#endif //XPLAY_IAUDIOPLAYER_H
