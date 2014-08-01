
#include "application.h"
#include "stdafx.h"


#define IDC_START_BTN 11001


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
    rct.right = 600;
    rct.bottom = 490;

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
        0, 50,
        620, 440,
        frame->GetHWND(), NULL, hInstance);

    CreateWindow(L"button",
        L"Start",
        WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
        10, 10, 100, 20,
        frame->GetHWND(),
        (HMENU)IDC_START_BTN,
        hInstance, 0);


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
    needUpdate = false;

    while (running)
    {
        lag += timer.GetTime();
        timer.Reset();

        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) { running = false; }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            GetInput(msg);
        }

        // while (lag >= MS_PER_UPDATE)
        if (needUpdate)
        {
            //std::cout << "Update ";
            Update();
            //needUpdate = false;
            lag -= MS_PER_UPDATE;
        }
        //std::cout << "Render\n";
        Render(lag/MS_PER_UPDATE);
    }
}


void Application::GetInput(const MSG & msg)
{
    if (msg.hwnd == viewport->GetHWND())
    {
        if (game) { game->HandleInput(msg); }
    }

    switch (msg.message)
    {
    case WM_COMMAND:
        switch (LOWORD(msg.wParam))
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
                case OFFLINE:
                    game = new Game(new Player(), new BotPlayer());
                    std::cout << "New game!\n";
                    break;

                case ONLINE_HOST:
                    Service::Provide(new Server(frame->GetHWND()));
                    Service::Network()->SetListener(this);
                    mainPlayer = new Player();
                    adversaryPlayer = new RemotePlayer();
                    game = new Game(mainPlayer, adversaryPlayer);
                    break;

                case ONLINE_CLIENT:
                    Service::Provide(new Client(frame->GetHWND()));
                    Service::Network()->SetListener(this);
                    mainPlayer = new Player();
                    adversaryPlayer = new RemotePlayer();
                    game = new Game(mainPlayer, adversaryPlayer);
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

    case WM_BUTTON_FEEDBACK:
        switch (LOWORD(msg.wParam))
        {
        case IDC_START_BTN:
            if (game)
            {
                game->PrepareStart();
            }
            break;

        default:
            break;
        }

    case WM_KEYDOWN:
        if (msg.wParam == VK_SPACE)
        {
            needUpdate = true;
        }
        break;

    case WM_SOCKET:
        {
            Service::Network()->HandleMessages(msg.wParam, msg.lParam);
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

    if (game)
    {
        game->Draw(hDC);
    }

    InvalidateRect(viewport->GetHWND(), NULL, FALSE);
}

