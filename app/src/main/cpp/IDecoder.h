//
// Created by xp.chen on 2018/12/14.
//

#ifndef XPLAY_IDECODER_H
#define XPLAY_IDECODER_H


#include "XParameters.h"
#include "XData.h"
#include "IObserver.h"

class IDecoder : IObserver{

public:
    /** 打开解码器，支持硬解码 */
    virtual bool Open(XParameters params) = 0;
    /** 发送数据到解码队列 */
    virtual bool SendPacket(XData pkt) = 0;
    /** 从解码队列中获取一帧数据 */
    virtual XData RecvFrame() = 0;

};


#endif //XPLAY_IDECODER_H
