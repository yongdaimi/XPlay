//
// Created by xp.chen on 2018/12/25.
//

#include "GLVideoView.h"
#include "XTexture.h"

void GLVideoView::SetRender(void *win) {
    view = win;
}

void GLVideoView::Render(XData data) {
    if (!view) return;
    if (!txt) {
        txt = XTexture::Cretea();
        txt->Init(view); // 同时完成初始化
    }
    txt->Draw(data.datas, data.width, data.height);
}
