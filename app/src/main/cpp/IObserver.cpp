//
// Created by xp.chen on 2018/12/12.
//

#include "IObserver.h"
#include "XLog.h"


void IObserver::Update(XData data)
{
    XLOGI("observer update data size is %d", data.size);
}

void IObserver::AddObserver(IObserver *observer)
{
    if (!observer) return;
    mutex.lock();
    obss.push_back(observer);
    mutex.unlock();
}

void IObserver::Notify(XData data)
{
    mutex.lock();
    for (int i = 0; i < obss.size(); i++) {
        obss[i]->Update(data);
    }
    mutex.unlock();
}

