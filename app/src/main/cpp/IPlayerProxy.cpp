//
// Created by xp.chen on 2019/01/30.
//

#include "IPlayerProxy.h"
#include "FFPlayerBuilder.h"

void IPlayerProxy::Init(void *vm )
{
    mux.lock();
    if (vm) {
        FFPlayerBuilder::InitHard(vm);
    }
    if (!player)
        player = FFPlayerBuilder::Get()->BuildPlayer();
    mux.unlock();
}


bool IPlayerProxy::Open(const char *path)
{
    bool re = false;
    mux.lock();
    if (player)
        re = player->Open(path);
    mux.unlock();
    return re;
}


bool IPlayerProxy::Start()
{
    bool re = false;
    mux.lock();
    if (player)
        re = player->Start();
    mux.unlock();
    return re;
}

void IPlayerProxy::InitView(void *win)
{
    mux.lock();
    if (player)
        player->InitView(win);
    mux.unlock();
}
