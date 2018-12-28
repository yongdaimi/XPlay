//
// Created by xp.chen on 2018/12/25.
//

#ifndef XPLAY_XTEXTURE_H
#define XPLAY_XTEXTURE_H


class XTexture {
public:
    virtual bool Init(void *win) = 0;
    static XTexture *Cretea();
    virtual void Draw(unsigned char *data[], int width, int height) = 0;

};


#endif //XPLAY_XTEXTURE_H
