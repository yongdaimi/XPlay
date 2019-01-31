//
// Created by xp.chen on 2018/12/14.
//

#ifndef XPLAY_FFDECODER_H
#define XPLAY_FFDECODER_H


#include "IDecoder.h"
#include <mutex>


struct AVCodecContext;
struct AVFrame;
class FFDecoder : public IDecoder{

public:
    /** 初始化硬解码 */
    static void initHard(void *vm);
    virtual bool Open(XParameters params, bool isSupportHard = false);
    /** 关闭操作 */
    virtual void Close();
    /** 发送数据到解码队列 */
    virtual bool SendPacket(XData pkt);
    /** 从解码队列中获取一帧数据 */
    virtual XData RecvFrame();

protected:
    AVCodecContext *avctx = 0;
    AVFrame        *frame = 0;
    std::mutex mux;
};

#endif //XPLAY_FFDECODER_H
