
#pragma once
#include <windows.h>

enum GameMode
{
    OFFLINE, ONLINE_HOST, ONLINE_CLIENT
};

struct NewGameParams
{
    GameMode gameMode;
    char ipAddress[20];
};

BOOL CALLBACK NewGameDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
