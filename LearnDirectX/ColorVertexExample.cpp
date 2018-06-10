//
// Created by JimmyLin on 2018/6/10.
//

#include <iostream>
#include "d3dUtility.h"

struct  ColorVertex{
    float x,y,z;
    D3DCOLOR color;
    ColorVertex(float _x,float _y,float _z,D3DCOLOR _color){
        x=_x;y=_y;z=_z;
        color=_color;
    }
    static const  DWORD FVF;
};
const DWORD ColorVertex::FVF=D3DFVF_XYZ|D3DFVF_DIFFUSE;


D3DXMATRIX worldMatrix;
IDirect3DDevice9 *Device = 0;
IDirect3DVertexBuffer9 *Triangle = 0;
const int Width = 800;
const int Height = 600;


bool Setup() {
    Device->CreateVertexBuffer(3 * sizeof(ColorVertex), D3DUSAGE_WRITEONLY, ColorVertex::FVF, D3DPOOL_MANAGED, &Triangle, 0);

    ColorVertex *vertices;
    Triangle->Lock(0, 0, (void **) &vertices, 0);
    vertices[0] = ColorVertex(-1.0f, 0.0f, 2.0f,D3DCOLOR_XRGB(255,0,0));
    vertices[1] =ColorVertex(0.0f, 1.0f, 2.0f,D3DCOLOR_XRGB(0,255,0));
    vertices[2] = ColorVertex(1.0f, 0.0f, 2.0f,D3DCOLOR_XRGB(0,0,255));
    Triangle->Unlock();


    D3DXVECTOR3 position(0.0f, 0.0f, -5.0f);
    D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
    D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
    D3DXMATRIX V;
    D3DXMatrixLookAtLH(&V, &position, &target, &up);
    Device->SetTransform(D3DTS_VIEW, &V);

    D3DXMATRIX proj;
    D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, (float) Width / (float) Height, 1.0f, 1000.0f);
    Device->SetTransform(D3DTS_PROJECTION, &proj);
    Device->SetRenderState(D3DRS_LIGHTING, false);
    return true;
}

bool Display(float deltaTIme) {
    if (Device) {
        Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
        Device->BeginScene();
        Device->SetFVF(ColorVertex::FVF);
        Device->SetStreamSource(0,Triangle,0,sizeof(ColorVertex));

        D3DXMatrixTranslation(&worldMatrix,-1.25f,0.0f,0.0f);
        Device->SetTransform(D3DTS_WORLD,&worldMatrix);
        Device->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_FLAT);
        Device->DrawPrimitive(D3DPT_TRIANGLELIST,0,1);
        Device->EndScene();

        Device->Present(0, 0, 0, 0);
    }
    return true;
}

void CLeanUp() {

}


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {

    if (!d3d::InitD3D(hinstance, Width, Height, true, D3DDEVTYPE_HAL, &Device)) {
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