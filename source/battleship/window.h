#pragma once

#include <windows.h>

class Window
{
public:
    Window() { hWnd = NULL; }

    virtual ~Window() { }

    virtual bool CreateEx(DWORD dwExStyle,
        LPCTSTR lpszClass, LPCTSTR lpszName,
        DWORD dwStyle,
        int x, int y,
        int nWidth, int nHeight,
        HWND hParent, HMENU hMenu, HINSTANCE hInst);

    bool RegClass(LPCTSTR lpszClass, HINSTANCE hInst);

    HWND GetHWND() const { return hWnd; }

    BOOL Show(int nCmdShow) const
    {
        return ::ShowWindow(hWnd, nCmdShow);
    }

    BOOL Update() const
    {
        return ::UpdateWindow(hWnd);
    }

protected:
    HWND hWnd;

    virtual LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    virtual void OnCreate() { }
    virtual void OnPaint(HDC hDC) { }
    virtual void OnKeyDown(WPARAM vkcode, LPARAM extraInfo) { }
    virtual void OnLeftMouseButtonDown(int x, int y) { }
    virtual void OnSize(int width, int height, WPARAM wParam) { }
    virtual void OnCommand(WPARAM wParam, LPARAM lParam) { }
    virtual void OnDestroy() { }

    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    virtual void FillWndClassEx(WNDCLASSEX & wcex);

};



