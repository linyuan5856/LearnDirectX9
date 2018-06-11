//
// Created by JimmyLin on 2018/6/10.
//

#include <iostream>
#include "d3dUtility.h"

struct NormalVertex {
    float x, y, z;
    float nx, ny, nz;

    NormalVertex(float _x, float _y, float _z, float _nx, float _ny, float _nz) {
        x = _x;
        y = _y;
        z = _z;
        nx = _nx;
        ny = _ny;
        nz = _nz;
    }

    static const DWORD FVF;
};

const DWORD NormalVertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL;


D3DXMATRIX worldMatrix;
IDirect3DDevice9 *Device = 0;
IDirect3DVertexBuffer9 *Triangle = 0;
const int Width = 800;
const int Height = 600;


bool Setup() {
    Device->SetRenderState(D3DRS_LIGHTING, true);
    Device->CreateVertexBuffer(12 * sizeof(NormalVertex), D3DUSAGE_WRITEONLY, NormalVertex::FVF, D3DPOOL_MANAGED,
                               &Triangle, 0);

    NormalVertex *vertices;
    Triangle->Lock(0, 0, (void **) &vertices, 0);
    vertices[0] = NormalVertex(-1.0f, 0.0f, -1.0f, 0.0f, 0.707f, 0.0f);
    vertices[1] = NormalVertex(0.0f, 1.0f, 0.0f, 0.0f, 0.707f, 0.0f);
    vertices[2] = NormalVertex(1.0f, 0.0f, -1.0f, 0.0f, 0.707f, 0.0f);

    vertices[3] = NormalVertex(-1.0f, 0.0f, 1.0f, -0.707f, 0.707f, 0.0f);
    vertices[4] = NormalVertex(0.0f, 1.0f, 0.0f, -0.707f, 0.707f, 0.0f);
    vertices[5] = NormalVertex(-1.0f, 0.0f, -1.0f, -0.707f, 0.707f, 0.0f);

    vertices[6] = NormalVertex(1.0f, 0.0f, -1.0f, 0.707f, 0.707f, 0.0f);
    vertices[7] = NormalVertex(0.0f, 1.0f, 0.0f, 0.707f, 0.707f, 0.0f);
    vertices[8] = NormalVertex(1.0f, 0.0f, 1.0f, 0.707f, 0.707f, 0.0f);

    vertices[9] = NormalVertex(1.0f, 0.0f, 1.0f, 0.0f, 0.707f, 0.0f);
    vertices[10] = NormalVertex(0.0f, 1.0f, 0.0f, 0.0f, 0.707f, 0.0f);
    vertices[11] = NormalVertex(-1.0f, 0.0f, -1.0f, 0.0f, 0.707f, 0.0f);
    Triangle->Unlock();

    D3DMATERIAL9 blueMaterial;
    blueMaterial = d3d::RED_MAT;
    Device->SetMaterial(&blueMaterial);
    D3DXVECTOR3 direction = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
    D3DCOLORVALUE lightColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    D3DLIGHT9 light = d3d::InitDirectionalLight(&direction, &lightColor);
    Device->SetLight(0, &light);
    Device->LightEnable(0, true);

    Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
    Device->SetRenderState(D3DRS_SPECULARENABLE, true);

    D3DXVECTOR3 position(0.0f, 0.0f, -4.0f);
    D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
    D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
    D3DXMATRIX V;
    D3DXMatrixLookAtLH(&V, &position, &target, &up);
    Device->SetTransform(D3DTS_VIEW, &V);

    D3DXMATRIX proj;
    D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, (float) Width / (float) Height, 1.0f, 1000.0f);
    Device->SetTransform(D3DTS_PROJECTION, &proj);
    return true;
}

bool Display(float deltaTIme) {
    if (Device) {
        Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
        Device->BeginScene();
        Device->SetFVF(NormalVertex::FVF);
        Device->SetStreamSource(0, Triangle, 0, sizeof(NormalVertex));

        D3DXMatrixIdentity( &worldMatrix );
        D3DXMatrixRotationX( &worldMatrix,deltaTIme);
       // D3DXMatrixTranslation(&worldMatrix, -0.25f, 0.0f, 0.0f);
        Device->SetTransform(D3DTS_WORLD, &worldMatrix);
        Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
        Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0,4);
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