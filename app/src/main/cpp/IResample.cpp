//
// Created by xp.chen on 2018/12/27.
//

#include "IResample.h"
#include "XLog.h"


void IResample::Update(XData data)
{
    XData d = this->Resample(data);
    if (d.size > 0) {
        this->Notify(d);
    }
}



