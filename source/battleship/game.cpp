
#include "game.h"
#include "stdafx.h"


Game::Game()
{

}


Game::~Game()
{
   
}


void Game::Init()
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

    AdjustWindowRectEx(&rct, WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL, TRUE, WS_EX_OVERLAPPEDWINDOW);

    bool res = viewport.CreateEx(WS_EX_OVERLAPPEDWINDOW,
        L"WP Lab 4",
        L"WP Lab 4",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0,
        rct.right - rct.left, rct.bottom - rct.top,
        NULL, NULL,
        GetModuleHandle(NULL));

    if (!res)
    {
        throw Error("Could not create the window!");
    }

    viewport.Show(SW_SHOW);
    viewport.Update();
}


void Game::SceneInit()
{
    
}


void Game::Run()
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
            if (needUpdate)
            {
                Update();
                needUpdate = true;
            }
            lag -= MS_PER_UPDATE;
        }

        Render(lag/MS_PER_UPDATE);
    }
}


void Game::GetInput(int message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_MOUSEMOVE:
        {
            POINT m;
            m.x = GET_X_LPARAM(lParam);
            m.y = GET_Y_LPARAM(lParam);

            mouse.Update(m.x, m.y);
        }
        break;
    case WM_LBUTTONDOWN:
        OnLeftButtonDown();
        break;

    case WM_MOUSEWHEEL:
        OnRightButtonDown();
        break;

    default:
        return;
    }
}


void Game::OnLeftButtonDown()
{
}


void Game::OnRightButtonDown()
{
    needUpdate = true;
}


void Game::Update()
{
   
}


void Game::Render(double inFrame)
{
   
}

