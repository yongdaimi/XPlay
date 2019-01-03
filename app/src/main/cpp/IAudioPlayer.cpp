//
// Created by xp.chen on 2018/12/28.
//

#include "IAudioPlayer.h"
#include "XLog.h"


void IAudioPlayer::Update(XData data)
{
    // 将重采样过来的音频数据压入缓冲队列
    // 解码的数据压入到缓冲队列当中，由另外一个线程从缓冲中取出数据来播放
    if (data.size <= 0 || !data.data) return;
    while (!isExit) {
        frameMutex.lock();
        if (frames.size() > maxFrame) {
            frameMutex.unlock();
            XSleep(1);
            continue;
        }
        XLOGI("IAudioPlayer:: Update() data size is: %d", data.size);
        frames.push_back(data);
        frameMutex.unlock();
        break;
    }
}


XData IAudioPlayer::GetData()
{
    XData d;
    while (!isExit) {
        frameMutex.lock();
        if (!frames.empty()) {
            d = frames.front();
            frames.pop_front();
            frameMutex.unlock();
            return d;
        }
        // 如果队列是空的
        frameMutex.unlock();
        XSleep(1);
    }
    return d;
}








