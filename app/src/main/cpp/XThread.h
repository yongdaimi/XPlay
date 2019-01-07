//
// Created by xp.chen on 2018/12/12.
//

#ifndef XPLAY_XTHREAD_H
#define XPLAY_XTHREAD_H

/** sleep 毫秒 */
void XSleep(int mis);

class XThread {

public:
    /** 启动线程 */
    virtual bool Start();
    /** 停止线程 */
    virtual void Stop();
    /** 线程入口函数 */
    virtual void Main(){};
private:
    /** 入口主函数 */
    void ThreadMain();

protected:
    /** 令线程退出的标识 */
    bool isExit = false;
    /** 线程是否退出的标识 */
    bool isRunning = false;
};


#endif //XPLAY_XTHREAD_H
