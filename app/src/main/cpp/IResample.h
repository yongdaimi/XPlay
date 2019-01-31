//
// Created by xp.chen on 2018/12/27.
//

#ifndef XPLAY_IRESAMPLE_H
#define XPLAY_IRESAMPLE_H


#include "IObserver.h"
#include "XParameters.h"

class IResample : public IObserver{
public:
    /** 输入参数可以直接从解封装器那儿获取，输出参数是需要配置 */
    virtual bool Open(XParameters in, XParameters out = XParameters()) = 0;
    /** 关闭操作 */
    virtual void Close() = 0;
    virtual XData Resample(XData inData) = 0;
    virtual void Update(XData data);
    /** 输出的通道数 */
    int outChannels = 2;
    int outFormat = 1;

};


#endif //XPLAY_IRESAMPLE_H
