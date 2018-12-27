package com.yuneec.android.xplay;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

public class XPlay extends GLSurfaceView implements SurfaceHolder.Callback {


    public XPlay(Context context) {
        super(context);
    }

    public XPlay(Context context, AttributeSet attrs) {
        super(context, attrs);
    }


    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        InitView(holder.getSurface());
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int var2, int var3, int var4) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }


    public native void InitView(Object surface);



}
