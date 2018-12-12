//
// Created by xp.chen on 2018/11/26.
//

#include "XData.h"

extern "C" {
#include <libavformat/avformat.h>
}

void XData::Drop() {
    if (!data) return;
    av_packet_free((AVPacket **)&data);
    data = 0;
    size = 0;
}


