//
// Created by xp.chen on 2018/12/28.
//

#ifndef XPLAY_IAUDIOPLAYER_H
#define XPLAY_IAUDIOPLAYER_H


#include <list>
#include "IObserver.h"
#include "XParameters.h"

class IAudioPlayer : public IObserver{
public:
    /** 接收重采样(IResample)过来的数据
     * 主要作用是向缓冲队列中插入数据
     * 当缓冲队列满了之后，会阻塞
     * */
    virtual void Update(XData data);
    virtual bool StartPlay(XParameters out) = 0;
    /** 获取缓冲数据 如果没有则阻塞 */
    virtual XData GetData();
    /** 缓冲队列中的最大元素个数 */
    int maxFrame = 100;

protected:
    std::list<XData> frames;
    std::mutex  frameMutex;
};


#endif //XPLAY_IAUDIOPLAYER_H
