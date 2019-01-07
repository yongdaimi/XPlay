//
// Created by xp.chen on 2018/12/12.
//

#include "XThread.h"
#include "XLog.h"
#include <thread>
using namespace std;


void XSleep(int mis)
{
    chrono::milliseconds du(mis);
    this_thread::sleep_for(du);
}

bool XThread::Start()
{
    isExit = false;
    thread th(&XThread::ThreadMain, this); // 使用C++ 11中的线程库实现
    th.detach(); // 当前线程放弃对该线程控制
    return true;
}

// 通过控制isExist安全停止线程，不一定成功
void XThread::Stop()
{
    isExit = true;
    for (int i = 0; i < 200; i++) {
        if (!isRunning) {
            XLOGI("线程退出成功");
            return;
        }
        XSleep(1);
    }
    XLOGI("线程退出超时");
}

void XThread::ThreadMain()
{
    XLOGI("线程函数进入");
    isRunning = true;
    Main();
    isRunning = false;
    XLOGI("线程函数退出");
}






