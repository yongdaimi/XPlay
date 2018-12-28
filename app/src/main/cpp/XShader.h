//
// Created by xp.chen on 2018/12/25.
//

#ifndef XPLAY_XSHADER_H
#define XPLAY_XSHADER_H


class XShader {
public:
    virtual bool Init();
    // 由它来获取材质。获取材质并映射到内存
    virtual void GetTexture(unsigned int index, int width, int height, unsigned char *buf);
    virtual void Draw();

protected:
    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
    unsigned int texts[100] = {0};
};


#endif //XPLAY_XSHADER_H
