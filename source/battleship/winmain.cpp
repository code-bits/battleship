#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "stdafx.h"


using namespace std;

map<string, string> g_options;
LPCWSTR g_mainWinClassName = L"lab3";
LPCWSTR g_viewportWinClassName = L"viewport";




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    Game* game = NULL;

    try
    {
        game = new Game();

        game->Init();
        game->SceneInit();
        game->Run();
    }
    catch (const Error& e)
    {
        cout << e.What();
    }

    if (game) { delete game; }
    return 0;
}
