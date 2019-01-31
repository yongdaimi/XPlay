//
// Created by xp.chen on 2018/12/14.
//

#ifndef XPLAY_IDECODER_H
#define XPLAY_IDECODER_H


#include "XParameters.h"
#include "XData.h"
#include "IObserver.h"
#include <list>

class IDecoder : public IObserver{

public:
    /** 打开解码器，支持硬解码 */
    virtual bool Open(XParameters params, bool isSupportHard = false) = 0;
    /** 关闭操作 */
    virtual void Close() = 0;
    /** 发送数据到解码队列 */
    virtual bool SendPacket(XData pkt) = 0;
    /** 从解码队列中获取一帧数据 */
    virtual XData RecvFrame() = 0;
    /** 则该方法接收发送过来的数据，
     * 注意：当数据给解码器之后，没有必要直接解码，正确的做法是将数据先
     * 放入到解码队列当中去*/
    virtual void Update(XData data);
    /** 标定当前解码器的类型(音频解码器/视频解码器) */
    bool isAudio = false;
    /** 队列缓冲的最大值 */
    int maxList = 100;
    /* 同步时间，再次打开文件要清理 */
    int synPts = 0;
    /** 表示当前播放的时间 */
    int pts = 0;

protected:
    virtual void Main();
    /** 读取缓冲，用于存放解封装器传递过来的数据 */
    std::list<XData> packs;
    /** 这个互斥变量是专门读取队列的互斥变量 */
    std::mutex packsMutex;
};


#endif //XPLAY_IDECODER_H
