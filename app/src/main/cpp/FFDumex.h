//
// Created by xp.chen on 2018/11/26.
//

#ifndef XPLAY_FFDUMEX_H
#define XPLAY_FFDUMEX_H

#include "IDumex.h"

struct AVFormatContext;
class FFDumex : public IDumex {

public:
    /** 打开文件或者流媒体(rtsp, rtmp, http) */
    virtual bool Open(const char *url);
    /** 读取一帧数据, 数据由调用者处理 */
    virtual XData Read();
    FFDumex();

private:
    AVFormatContext *ic = 0;
};


#endif //XPLAY_FFDUMEX_H
