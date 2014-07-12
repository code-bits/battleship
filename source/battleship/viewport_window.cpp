
#include "viewport_window.h"
#include "stdafx.h"


void ViewportWindow::FillWndClassEx(WNDCLASSEX & wcex)
{
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
}


void ViewportWindow::OnCreate()
{
    RECT rct;
    GetClientRect(hWnd, &rct);

    int width = rct.right - rct.left;
    int height = rct.bottom - rct.top;

    HDC hDC = GetDC(hWnd);

    backbuffer.Init(hDC, width, height);

    ReleaseDC(hWnd, hDC);
}


void ViewportWindow::OnPaint(HDC hDC)
{
    backbuffer.Present(hDC);
}


void ViewportWindow::OnSize(int width, int height, WPARAM wParam)
{
    backbuffer.Resize(width, height);
}


LRESULT ViewportWindow::WndProc(HWND hWnd_, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_ERASEBKGND:
        return 1;

    default:
        return Window::WndProc(hWnd_, message, wParam, lParam);
    }

    return 0;
}
