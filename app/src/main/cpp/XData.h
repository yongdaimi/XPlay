//
// Created by xp.chen on 2018/11/26.
//

#ifndef XPLAY_XDATA_H
#define XPLAY_XDATA_H


struct XData {
    unsigned char *data;
    int size;
    bool isAudio = false;
    void Drop();
};


#endif //XPLAY_XDATA_H
