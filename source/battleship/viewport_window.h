#pragma once


#include <windows.h>
#include "window.h"
#include "backbuffer.h"



class ViewportWindow : public Window
{
public:
    ViewportWindow();
    void InitCanvas(int w, int h);
    int GetWidth() { return width; }
    int GetHeight() { return height; }
    Backbuffer* GetBackbuffer() { return &backbuffer; }

private:
    int width;
    int height;
    Backbuffer backbuffer;


    virtual void OnCreate();
    virtual void OnPaint(HDC hDC);
    virtual void OnSize(int width, int height, WPARAM wParam);
    virtual void OnDestroy();



    virtual LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual void FillWndClassEx(WNDCLASSEX & wcex);
};