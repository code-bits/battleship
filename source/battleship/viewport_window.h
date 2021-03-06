#pragma once


#include <windows.h>
#include "window.h"
#include "backbuffer.h"



class ViewportWindow : public Window
{
public:
    Backbuffer* GetBackbuffer() { return &backbuffer; }

private:
    Backbuffer backbuffer;

    virtual void OnCreate();
    virtual void OnPaint(HDC hDC);
    virtual void OnSize(int width, int height, WPARAM wParam);

    virtual LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    virtual void FillWndClassEx(WNDCLASSEX & wcex);
};
