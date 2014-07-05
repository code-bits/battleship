
#include "viewport_window.h"
#include "stdafx.h"


ViewportWindow::ViewportWindow()
{

}


void ViewportWindow::FillWndClassEx(WNDCLASSEX & wcex)
{
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
}


void ViewportWindow::OnCreate()
{
    RECT rct;
    GetClientRect(hWnd, &rct);

    width = rct.right - rct.left;
    height = rct.bottom - rct.top;

    HDC hDC = GetDC(hWnd);

    backbuffer.Init(hDC, width, height);

    ReleaseDC(hWnd, hDC);

}


void ViewportWindow::OnPaint(HDC hDC)
{
    backbuffer.Present(hDC);
}


void ViewportWindow::OnSize(int width_, int height_, WPARAM wParam)
{
    width = width_;
    height = height_;
    backbuffer.Resize(width, height);
}


void ViewportWindow::OnDestroy()
{
    PostQuitMessage(0);
}


LRESULT ViewportWindow::WndProc(HWND hWnd_, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_ERASEBKGND:
        return 1;
        break;


    case WM_LBUTTONDOWN:
        SetCapture(hWnd);
        //mouse.LeftButtonDown();
        break;


    case WM_LBUTTONUP:
        ReleaseCapture();
        //mouse.LeftButtonUp();
        break;


    case WM_RBUTTONDOWN:
        SetCapture(hWnd);
        //mouse.RightButtonDown();
        break;


    case WM_RBUTTONUP:
        ReleaseCapture();
        //mouse.RightButtonUp();
        break;

    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;

    default:
        return Window::WndProc(hWnd_, message, wParam, lParam);
    }

    return 0;
}
