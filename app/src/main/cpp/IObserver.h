//
// Created by xp.chen on 2018/12/12.
//

#ifndef XPLAY_IOBSERVER_H
#define XPLAY_IOBSERVER_H


#include <vector>
#include <mutex>
#include "XData.h"
#include "XThread.h"


class IObserver : public XThread {

public:
    /** 通知观察者 */
    virtual void Update(XData data);
    /** 添加观察者(线程安全) */
    virtual void AddObserver(IObserver *observer);
    /** 通知所有观察者(线程安全) */
    virtual void Notify(XData data);

private:
    std::vector<IObserver *> obss;
    std::mutex mutex;
};


#endif //XPLAY_IOBSERVER_H
