//
// Created by xp.chen on 2018/12/14.
//

#include "IDecoder.h"
#include "XLog.h"


/** 消费者 */
void IDecoder::Main()
{
    while (!isExit) {
        packsMutex.lock();
        if (packs.empty()) {
            packsMutex.unlock();
            XSleep(1);
            continue;
        }
        // 取出packet
        XData pack = packs.front();
        packs.pop_front(); // 把对象从链表中删除
        // 发送数据到解码线程
        XLOGI("IDecoder:: Send Packet to decoder thread...");
        if (this->SendPacket(pack)) {
            while (!isExit) {
                // 获取解码数据
                XData frame = RecvFrame(); // 再次调用会复用上次空间，线程不安全
                if (!frame.data) break; // 如果读不到数据就返回
                XLOGI("IDecoder:: Receive frame %d", frame.size);
                // 通知所有观察者
                this->Notify(frame);
            }
        }
        pack.Drop(); // 释放数据
        packsMutex.unlock();
    }
}


/** 生产者 */
void IDecoder::Update(XData data)
{
    // 如果数据类型与解码器类型不一致，则不做任何处理
    if (data.isAudio != isAudio) {
        return;
    } else {
        while (!isExit) {
            packsMutex.lock();
            if (packs.size() < maxList) {
                packs.push_back(data);
                packsMutex.unlock();
                break;
            }
            packsMutex.unlock();
            XSleep(1);
        }
    }
}

