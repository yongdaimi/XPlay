//
// Created by xp.chen on 2018/12/25.
//

#ifndef XPLAY_XEGL_H
#define XPLAY_XEGL_H


class XEGL {
public:
    virtual bool Init(void *win) = 0;
    static XEGL *Get();

protected:
    XEGL(){};
};


#endif //XPLAY_XEGL_H
