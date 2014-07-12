
#include "application.h"
#include "stdafx.h"


Application::Application()
{

}


Application::~Application()
{

}


void Application::Init()
{
    INITCOMMONCONTROLSEX ctls;
    ctls.dwSize = sizeof(INITCOMMONCONTROLSEX);
    ctls.dwICC = ICC_BAR_CLASSES;

    InitCommonControlsEx(&ctls);

    CreateDeveloperConsole();

    RECT rct;

    rct.left = 0;
    rct.top = 0;
    rct.right = 800;
    rct.bottom = 600;

    AdjustWindowRectEx(&rct, WS_OVERLAPPEDWINDOW, TRUE, WS_EX_OVERLAPPEDWINDOW);

    HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
    HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

    frame = new FrameWindow();

    frame->CreateEx(WS_EX_OVERLAPPEDWINDOW,
        L"Battleship",
        L"Battleship",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0,
        rct.right - rct.left, rct.bottom - rct.top,
        NULL, hMenu, hInstance);

    viewport = new ViewportWindow();

    viewport->CreateEx(WS_EX_OVERLAPPEDWINDOW,
        L"Viewport",
        L"Viewport",
        WS_CHILD|WS_VISIBLE,
        10, 50,
        780, 580,
        frame->GetHWND(), NULL, hInstance);


    frame->Show(SW_SHOW);
    frame->Update();
}


void Application::SceneInit()
{

}


void Application::Run()
{

    MSG msg;
    bool running = true;

    double lag = 0.0;
    const double MS_PER_UPDATE = 16.66666;
    Timer timer;

    while (running)
    {
        lag += timer.GetTime();
        timer.Reset();

        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) { running = false; }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            GetInput(msg.message, msg.wParam, msg.lParam);
        }

        while (lag >= MS_PER_UPDATE)
        {
            Update();
            lag -= MS_PER_UPDATE;
        }

        Render(lag/MS_PER_UPDATE);
    }
}


void Application::GetInput(int message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    default:
        return;
    }
}


void Application::OnLeftButtonDown()
{

}


void Application::OnRightButtonDown()
{

}


void Application::Update()
{

}


void Application::Render(double inFrame)
{
    Backbuffer* bb = viewport->GetBackbuffer();
    bb->FillWithColor(RGB(200, 100, 100));
    HDC hDC = bb->GetDC();

    //leftFiledDrawer->Draw(hDC, firstPlayer->GetField().GetCells());
    static int a = 10;
    Rectangle(hDC, a, 10, a+100, 100);
    ++a;
    a %= 500;

    InvalidateRect(viewport->GetHWND(), NULL, FALSE);
}

