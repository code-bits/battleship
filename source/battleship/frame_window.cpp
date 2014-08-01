
#include "frame_window.h"
#include "stdafx.h"


void FrameWindow::FillWndClassEx(WNDCLASSEX & wcex)
{
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
}


void FrameWindow::OnCreate()
{

}


void FrameWindow::OnSize(int width, int height, WPARAM wParam)
{

}


void FrameWindow::OnDestroy()
{
    PostQuitMessage(0);
}


LRESULT FrameWindow::WndProc(HWND hWnd_, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        if (HIWORD(wParam) == BN_CLICKED)
        {
            PostMessage(hWnd, WM_BUTTON_FEEDBACK, wParam, lParam);
        }
        break;

    default:
        return Window::WndProc(hWnd_, message, wParam, lParam);
    }

    return 0;
}

