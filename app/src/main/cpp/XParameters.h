//
// Created by xp.chen on 2018/12/14.
//

#ifndef XPLAY_XPARAMETERS_H
#define XPLAY_XPARAMETERS_H


struct AVCodecParameters;
class XParameters {

public:
    AVCodecParameters *params = 0;
    int channels = 2; // 通道数
    int sample_rate = 44100; // 样本率

};


#endif //XPLAY_XPARAMETERS_H
