//
// Created by xp.chen on 2018/12/25.
//

#include "XTexture.h"
#include "XLog.h"
#include "XEGL.h"
#include "XShader.h"

class CXTexture : public XTexture
{
public:
    XShader sh;
    virtual bool Init(void *win) {
        if (!win) {
            XLOGE("CXTexture:: Init() failed, win is null");
            return false;
        }
        if (!XEGL::Get()->Init(win)) return false;
        sh.Init();
        return false;
    }
};


XTexture *XTexture::Cretea()
{
    return new CXTexture();
}








