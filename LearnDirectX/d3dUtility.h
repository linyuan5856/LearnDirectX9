//
// Created by JimmyLin on 2018/6/7.
//

#ifndef GAMEENGINE_D3DUTILITY_H
#define GAMEENGINE_D3DUTILITY_H

#include<d3dx9.h>
#include <string>

namespace d3d {
    bool InitD3D(
            HINSTANCE hInstance, //当前应用程序实例的句柄
            int width, int height, //后台缓存的表面宽度和高度
            bool windowed, //是否窗口化
            D3DDEVTYPE deviceType, //D3D设备类型  硬件（HAL）或者引用（REF）或软件（SW）
            IDirect3DDevice9 **device);//以创建的设备（用于输出）

    int EnterMsgLoop(
            bool(*ptr_display)(float timeDelta));

    LRESULT CALLBACK WndProc(
            HWND hwnd,
            UINT msg,
            WPARAM wParam,
            LPARAM lParam);

    template<class T>
    void Release(T t) {
        if (t) {
            t->Release();
            t = 0;
        }
    }

    template<class T>
    void Delete(T t) {
        if (t) {
            delete t;
            t = 0;
        }
    }

    const D3DXCOLOR WHITE(D3DCOLOR_XRGB(255,255,255));
    const D3DXCOLOR BLACK(D3DCOLOR_XRGB(0,0,0));
    const D3DXCOLOR RED(D3DCOLOR_XRGB(255,0,0));
    const D3DXCOLOR GREEN(D3DCOLOR_XRGB(0,255,0));
    const D3DXCOLOR BLUE(D3DCOLOR_XRGB(0,0,255));
    const D3DXCOLOR YELLOW(D3DCOLOR_XRGB(255,255,0));
    const D3DXCOLOR CYAN(D3DCOLOR_XRGB(0,255,255));
    const D3DXCOLOR MAGENTA(D3DCOLOR_XRGB(255,0,255));

    D3DMATERIAL9 InitMaterial(D3DXCOLOR,D3DXCOLOR,D3DXCOLOR,D3DXCOLOR,float);

    const D3DMATERIAL9 WHITE_MAT=InitMaterial(WHITE,WHITE,WHITE,BLACK,8.0F);
    const D3DMATERIAL9 RED_MAT=InitMaterial(RED,RED,RED,BLACK,8.0F);
    const D3DMATERIAL9 GREEN_MAT=InitMaterial(GREEN,GREEN,GREEN,BLACK,8.0F);
    const D3DMATERIAL9 BLUE_MAT=InitMaterial(BLUE,BLUE,BLUE,BLACK,8.0F);
    const D3DMATERIAL9 YELLOW_MAT=InitMaterial(YELLOW,YELLOW,YELLOW,BLACK,8.0F);


    D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3*direction,D3DCOLORVALUE*color);
    D3DLIGHT9 InitPointLight(D3DXVECTOR3*pos,D3DCOLORVALUE*color);
    D3DLIGHT9 InitSpotLight(D3DXVECTOR3*pos,D3DXVECTOR3*direction,D3DCOLORVALUE*color);
}

#endif //GAMEENGINE_D3DUTILITY_H
