
#pragma once

#include "window.h"

#define WM_BUTTON_FEEDBACK (WM_USER + 2)

class FrameWindow : public Window
{
private:
    virtual void OnCreate();
    virtual void OnSize(int width, int height, WPARAM wParam);
    virtual void OnDestroy();

    virtual LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    virtual void FillWndClassEx(WNDCLASSEX & wcex);
};
