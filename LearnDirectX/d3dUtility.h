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
}

#endif //GAMEENGINE_D3DUTILITY_H
