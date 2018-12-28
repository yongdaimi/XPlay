//
// Created by xp.chen on 2018/12/27.
//

#ifndef XPLAY_FFRESAMPLE_H
#define XPLAY_FFRESAMPLE_H


#include "IResample.h"

struct SwrContext;
class FFResample : public IResample{

public:
    /** 输入参数可以直接从解封装器那儿获取，输出参数是需要配置 */
    virtual bool Open(XParameters in, XParameters out = XParameters());
    virtual XData Resample(XData inData);

protected:
    SwrContext *actx = 0;

};


#endif //XPLAY_FFRESAMPLE_H
