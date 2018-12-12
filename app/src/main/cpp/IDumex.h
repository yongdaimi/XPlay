//
// Created by xp.chen on 2018/11/26.
//

#ifndef XPLAY_IDUMEX_H
#define XPLAY_IDUMEX_H


#include "XData.h"
#include "XThread.h"
#include "IObserver.h"

class IDumex : public IObserver{

public:
    /** 打开文件或者流媒体(rtsp, rtmp, http) */
    virtual bool Open(const char *url) = 0;
    /** 读取一帧数据, 数据由调用者处理 */
    virtual XData Read() = 0;

    /** 总时长(毫秒) */
    int totalMs = 0;
protected:
    void Main();
};


#endif //XPLAY_IDUMEX_H
