//
// Created by xp.chen on 2018/11/26.
//

#ifndef XPLAY_XDATA_H
#define XPLAY_XDATA_H


enum XDataType
{
    AVPACKET_TYPE = 0,
    UCHAR_TYPE = 1
};


struct XData {
    int type = 0;
    int pts = 0;
    unsigned char *data = 0;
    int size = 0;
    bool isAudio = false;
    unsigned char *datas[8] = {0};
    int width = 0; // 视频宽度
    int height = 0; // 视频高度
    int format = 0; // 数据格式
    bool Alloc(int size, const char *data = 0);
    void Drop();
};


#endif //XPLAY_XDATA_H
