//
// Created by xp.chen on 2018/12/14.
//

#ifndef XPLAY_FFDECODER_H
#define XPLAY_FFDECODER_H


#include "IDecoder.h"

struct AVCodecContext;
struct AVFrame;
class FFDecoder : public IDecoder{

public:
    virtual bool Open(XParameters params);
    /** 发送数据到解码队列 */
    virtual bool SendPacket(XData pkt);
    /** 从解码队列中获取一帧数据 */
    virtual XData RecvFrame();

protected:
    AVCodecContext *avctx = 0;
    AVFrame        *frame = 0;

};


#endif //XPLAY_FFDECODER_H
