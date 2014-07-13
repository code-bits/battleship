
#include "frame_window.h"
#include "stdafx.h"


void FrameWindow::FillWndClassEx(WNDCLASSEX & wcex)
{
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
}


void FrameWindow::OnCreate()
{
    CreateWindow(L"button", L"button", WS_CHILD|WS_VISIBLE, 10, 10, 100, 20, hWnd, 0, 0, 0);
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

    default:
        return Window::WndProc(hWnd_, message, wParam, lParam);
    }

    return 0;
}

