#include <iostream>
#include "d3dUtility.h"


using namespace std;

IDirect3DDevice9 *Device = 0;

bool Setup() {
    return true;
}

void CLeanUp() {

}

bool Display(float deltaTIme) {
    if (Device) {
        Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
        Device->Present(0, 0, 0, 0);
    }
   return true;
}
LRESULT  CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_DESTROY:
            ::PostQuitMessage(0);
            break;
        case WM_KEYDOWN:
            if (wparam == VK_ESCAPE)
                ::DestroyWindow(hwnd);
            break;
    }
    return ::DefWindowProc(hwnd, msg, wparam, lparam);
}

    int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {

        if (!d3d::InitD3D(hinstance, 800, 600, true, D3DDEVTYPE_HAL, &Device)) {
            ::MessageBox(0, "InitD3D()-->Failed", 0, 0);
            return 0;
        }

        if (!Setup()) {
            ::MessageBox(0, "Setup()-->Failed", 0, 0);
            return 0;
        }

        d3d::EnterMsgLoop(Display);

        CLeanUp();

        Device->Release();

        return 0;
    }







