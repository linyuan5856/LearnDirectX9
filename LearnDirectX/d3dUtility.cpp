#include <iostream>
#include "d3dUtility.h"

bool d3d::InitD3D(HINSTANCE hInstance, int width, int height, bool windowed, D3DDEVTYPE deviceType,
                  IDirect3DDevice9 **device) {
    WNDCLASS wc;

    wc.style = CS_HREDRAW | CS_VREDRAW;//窗口类型（当水平长度，垂直长度，或者位置改变，重画整个窗口）
    wc.lpfnWndProc = (WNDPROC) d3d::WndProc;//窗口处理函数
    wc.cbClsExtra = 0;//窗口类无扩展
    wc.cbWndExtra = 0;//窗口实例无扩展
    wc.hInstance = hInstance;//实例句柄
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);//窗口最小化的图标为缺省图标
    wc.hCursor = LoadCursor(0, IDC_ARROW);//窗口采用箭头光标
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);//窗口的背景颜色为白色
    wc.lpszMenuName = 0;//窗口无菜单
    wc.lpszClassName = "Direct3D9App"; //窗口类名

    if (!RegisterClass(&wc))//如果注册失败，发出警告  
    {
        ::MessageBox(0, "RegisterClass() - FALIED", 0, 0);
        /** 
        MessageBox(HWND hWnd,LPCTSTR lpText,LPCTSTR lpCaption,UINT uType); 
        hWnd : 消息框拥有的窗口 
        lpText :消息框的内容 
        lpCaption :消息框的标题 
        uType :指定标志中的一个来显示消息框的按钮以及图标（默认，只有一个确认按钮） 
        **/
        return false;
    }

    HWND hwnd = 0;
    hwnd = ::CreateWindow("Direct3D9App", "Direct3D9App",
                          WS_EX_TOPMOST,//设置窗口风格，将窗口设为置顶
                          0, 0, width, height,
                          0/*父窗口*/, 0/*菜单*/, hInstance, 0/*扩展*/);
    if (!hwnd) {
        ::MessageBox(0, "CreateWindow() - FALIED", 0, 0);
        return false;
    }

    ::ShowWindow(hwnd, SW_SHOW);
    ::UpdateWindow(hwnd);

    HRESULT hr = 0;

    //步骤1：创建 IDirect3D9 对象  
    IDirect3D9 *d3d9 = 0;
    d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

    if (!d3d9) {
        ::MessageBox(0, "Direct3DCreate9() - FAILED", 0, 0);
        return false;
    }

    //步骤2：校验硬件顶点计算  

    D3DCAPS9 caps;
    d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);
    //caps会返回装载着当前显卡设备能力的信息  

    int vp = 0;
    if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
        vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
    else
        vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

    //步骤3：填充D3DPRESENT_PARAMETERS 结构的初始值  

    D3DPRESENT_PARAMETERS d3dpp;
    d3dpp.BackBufferWidth = width;
    d3dpp.BackBufferHeight = height;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.MultiSampleQuality = 0;
    d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hwnd;
    d3dpp.Windowed = windowed;
    d3dpp.EnableAutoDepthStencil = true;//若设置为true,则D3D自动创建并维护深度缓存或模板缓存  
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;//D24S8用24位表示深度并将8位保留供模板使用  
    d3dpp.Flags = 0;
    d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//刷新频率设为默认值  
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;//当交换链中后台缓存切换到前台缓的时候最大速率设为立即提交  


    //步骤 4：创建设备  
    hr = d3d9->CreateDevice(
            D3DADAPTER_DEFAULT,//主适配器
            deviceType,
            hwnd,
            vp,
            &d3dpp,
            device);           //返回创建的设备

    if (FAILED(hr)) {

        d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

        hr = d3d9->CreateDevice(D3DADAPTER_DEFAULT, deviceType, hwnd, vp, &d3dpp, device);

        if (FAILED(hr)) {
            d3d9->Release();
            ::MessageBox(0, "CreateDevice - FAILED", 0, 0);
            return false;
        }
    }

    d3d9->Release();

    return true;
}

int d3d::EnterMsgLoop(bool(*ptr_display)(float timeDelta)) {
    MSG msg;
    ::ZeroMemory(&msg, sizeof(MSG));

    static float lastTime = (float) timeGetTime();

    while (msg.message != WM_QUIT) {

        if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);//发出消息
        } else {
            float currTime = (float) timeGetTime();
            float timeDelta = (currTime - lastTime) * 0.001f;

            ptr_display(timeDelta);

            lastTime = currTime;
        }
    }
    return msg.wParam;//来自一条表示退出的消息  
}

