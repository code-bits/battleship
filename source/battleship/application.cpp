
#include "application.h"
#include "stdafx.h"


Application::Application()
{
    mainPlayer = NULL;
    adversaryPlayer = NULL;
    game = NULL;
}


Application::~Application()
{
    WSACleanup();
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

    viewport->CreateEx(0,
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
            GetInput(msg.hwnd, msg.message, msg.wParam, msg.lParam);
        }

        while (lag >= MS_PER_UPDATE)
        {
            Update();
            lag -= MS_PER_UPDATE;
        }

        Render(lag/MS_PER_UPDATE);
    }
}


void Application::GetInput(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
        if (hWnd == viewport->GetHWND())
        {
            int x = GET_X_LPARAM(lParam);
            int y = GET_Y_LPARAM(lParam);
            FieldDisplayParams fdp;
            fdp.x = 20;
            fdp.y = 20;
            fdp.size = 200;
            CellCoord cc;
            if (mainPlayer->personalField.Click(x, y, fdp, &cc))
            {
                mainPlayer->personalField.Set(cc, ALIVE);
            }

            fdp.x = 400;
            if (mainPlayer->adversaryField.Click(x, y, fdp, &cc))
            {
                if (mainPlayer->CanMove())
                {
                    std::cout << "Move " << cc.row << " " << cc.col << std::endl;
                    game->CheckCellOf(adversaryPlayer, mainPlayer, cc);
                }
            }
        }
        break;

    case WM_COMMAND:
        switch (LOWORD (wParam))
        {
        case IDM_GAME_NEW:
            NewGameParams ngp;
            if (DialogBoxParam(
                (HINSTANCE)GetWindowLong(frame->GetHWND(), GWL_HINSTANCE),
                MAKEINTRESOURCE(IDD_NEWGAME_DIALOG),
                frame->GetHWND(),
                NewGameDlgProc,
                (LPARAM) & ngp))
            {
                switch (ngp.gameMode)
                {
                case ONLINE_HOST:
                    Service::Provide(new Server(frame->GetHWND()));
                    Service::Network()->SetListener(this);
                    mainPlayer = new Player();
                    adversaryPlayer = new RemotePlayer();
                    game = new Game();
                    break;

                case ONLINE_CLIENT:
                    Service::Provide(new Client(frame->GetHWND()));
                    Service::Network()->SetListener(this);
                    mainPlayer = new Player();
                    adversaryPlayer = new RemotePlayer();
                    game = new Game();
                    mainPlayer->Move();
                    break;
                }
            }
            break;

        case IDM_GAME_QUIT:
            SendMessage(frame->GetHWND(), WM_CLOSE, 0, 0);
            break;
        }
        break;

    case WM_SOCKET:
        {
            Service::Network()->HandleMessages(wParam, lParam);
        }
        break;

    default:
        return;
    }
}


void Application::OnNetworkRead(const std::string & msgString)
{
    std::cout << "Received message: " << msgString << std::endl;
    Message msg = Message::Decode(msgString);

    if (msg.action == "check")
    {
        game->CheckCellOf(mainPlayer, adversaryPlayer, msg.cellCoords);
    }

    if (msg.action == "miss")
    {
        game->ReportMissTo(mainPlayer, adversaryPlayer, msg.cellCoords);
    }

    if (msg.action == "hit")
    {
        game->ReportHitTo(mainPlayer, adversaryPlayer, msg.cellCoords);
    }

    if (msg.action == "kill")
    {
        game->ReportKillTo(mainPlayer, adversaryPlayer, msg.cellCoords);
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
    //adversaryPlayer->Update(mainPlayer, game);
    if (game)
    {
        game->Update();
    }
}


void Application::Render(double inFrame)
{
    Backbuffer* bb = viewport->GetBackbuffer();
    bb->FillWithColor(RGB(200, 100, 100));
    HDC hDC = bb->GetDC();

    if (mainPlayer)
    {
        FieldDisplayParams fdp;
        fdp.x = 20;
        fdp.y = 20;
        fdp.size = 200;

        mainPlayer->personalField.Draw(hDC, fdp);

        fdp.x = 400;
        mainPlayer->adversaryField.Draw(hDC, fdp);
    }

    InvalidateRect(viewport->GetHWND(), NULL, FALSE);
}

