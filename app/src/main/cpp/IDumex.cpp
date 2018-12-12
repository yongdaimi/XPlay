//
// Created by xp.chen on 2018/11/26.
//

#include "IDumex.h"
#include "XLog.h"


void IDumex::Main()
{
    while (!isExit) {
        XData data = Read();
        if (data.size > 0) {
            Notify(data);
        }
        // XLOGI("IDumex::data size is: %d", data.size);
        // if (data.size <= 0) break;
    }
}

