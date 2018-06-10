#include <iostream>
#include "d3dUtility.h"


using namespace std;

IDirect3DDevice9 *Device = 0;
IDirect3DVertexBuffer9 *VB = 0;
IDirect3DIndexBuffer9 *IB = 0;
const int Width = 800;
const int Height = 600;

struct Vertex {
    Vertex() {}
    float _x, _y, _z;

    Vertex(float x, float y, float z) {
        _x = x;
        _y = y;
        _z = z;
    }
    static const DWORD FVF;
};

const DWORD Vertex::FVF = D3DFVF_XYZ;

bool Setup() {
    Device->CreateVertexBuffer(8 * sizeof(Vertex), D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_MANAGED, &VB, 0);
    Device->CreateIndexBuffer(36 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &IB, 0);
    Vertex *vertices;
    VB->Lock(0, 0, (void **) &vertices, 0);
    vertices[0] = Vertex(-1.0f, -1.0f, -1.0f);
    vertices[1] = Vertex(-1.0f, 1.0f, -1.0f);
    vertices[2] = Vertex(1.0f, 1.0f, -1.0f);
    vertices[3] = Vertex(1.0f, -1.0f, -1.0f);
    vertices[4] = Vertex(-1.0f, -1.0f, 1.0f);
    vertices[5] = Vertex(-1.0f, 1.0f, 1.0f);
    vertices[6] = Vertex(1.0f, 1.0f, 1.0f);
    vertices[7] = Vertex(1.0f, -1.0f, 1.0f);
    VB->Unlock();

    WORD *indices = 0;
    IB->Lock(0, 0, (void **) &indices, 0);
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 2;
    indices[5] = 3;
    indices[6] = 4;
    indices[7] = 6;
    indices[8] = 5;
    indices[9] = 4;
    indices[10] = 7;
    indices[11] = 6;
    indices[12] = 4;
    indices[13] = 5;
    indices[14] = 1;
    indices[15] = 4;
    indices[16] = 1;
    indices[17] = 0;
    indices[18] = 3;
    indices[19] = 2;
    indices[20] = 6;
    indices[21] = 3;
    indices[22] = 6;
    indices[23] = 7;
    indices[24] = 1;
    indices[25] = 5;
    indices[26] = 6;
    indices[27] = 1;
    indices[28] = 6;
    indices[29] = 2;
    indices[30] = 4;
    indices[31] = 0;
    indices[32] = 3;
    indices[33] = 4;
    indices[34] = 3;
    indices[35] = 7;
    IB->Unlock();

    D3DXVECTOR3 position(0.0f, 0.0f, -5.0f);
    D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
    D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
    D3DXMATRIX V;
    D3DXMatrixLookAtLH(&V, &position, &target, &up);
    Device->SetTransform(D3DTS_VIEW, &V);

    D3DXMATRIX proj;
    D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, (float) Width / (float) Height, 1.0f, 1000.0f);
    Device->SetTransform(D3DTS_PROJECTION, &proj);
    Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
    return true;
}

bool Display(float deltaTIme) {
    if (Device) {
        D3DXMATRIX Rx, Ry;
        D3DXMatrixRotationX(&Rx, 3.14f / 4.0f);
        static float y = 0;
        D3DXMatrixRotationY(&Ry, y);
        y += deltaTIme;
        if (y > 6.28f)
            y = 0.0f;

        D3DXMATRIX p = Rx * Ry;
        Device->SetTransform(D3DTS_WORLD, &p);

        Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);

        Device->BeginScene();
        Device->SetStreamSource(0,VB,0,sizeof(Vertex));
        Device->SetIndices(IB);
        Device->SetFVF(Vertex::FVF);
        Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,8,0,12);
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