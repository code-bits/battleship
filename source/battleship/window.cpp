
#include "window.h"
#include "stdafx.h"


Window::Window()
{
    hWnd = NULL;
}


void Window::CreateEx(DWORD dwExStyle,
               LPCTSTR lpszClass, LPCTSTR lpszName,
               DWORD dwStyle,
               int x, int y,
               int nWidth, int nHeight,
               HWND hParent, HMENU hMenu, HINSTANCE hInstance)
{
    if (!RegClass(lpszClass, hInstance))
    {
        throw Error("Could not register window class!");
    }

    MDICREATESTRUCT mdic;
    memset(&mdic, 0, sizeof(mdic));
    mdic.lParam = (LPARAM)this;


    hWnd = CreateWindowEx(dwExStyle,
        lpszClass, lpszName,
        dwStyle,
        x, y, nWidth, nHeight,
        hParent, hMenu, hInstance, &mdic);

    if (!hWnd)
    {
        throw Error("Error while creating the window!");
    }
}


bool Window::RegClass(LPCTSTR lpszClass, HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    if (!GetClassInfoEx(hInstance, lpszClass, &wcex))
    {
        wcex.cbSize         = sizeof(WNDCLASSEX);
        wcex.style          = 0;
        wcex.lpfnWndProc    = WindowProc;
        wcex.cbClsExtra     = 0;
        wcex.cbWndExtra     = 0;
        wcex.hInstance      = NULL;
        wcex.hIcon          = NULL;
        wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wcex.lpszMenuName   = NULL;
        wcex.lpszClassName  = NULL;
        wcex.hIconSm        = NULL;

        FillWndClassEx(wcex);

        wcex.hInstance = hInstance;
        wcex.lpszClassName = lpszClass;

        if (!RegisterClassEx(&wcex)) { return false; }
    }

    return true;
}


void Window::FillWndClassEx(WNDCLASSEX & wcex)
{

}



LRESULT Window::WndProc(HWND hWnd_, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_CREATE:
        hWnd = hWnd_;
        OnCreate();
        break;

    case WM_SIZE:
        {
            OnSize(LOWORD(lParam), HIWORD(lParam), wParam);
        }
        break;

    case WM_COMMAND:
        OnCommand(wParam, lParam);
        break;

    case WM_KEYDOWN:
        OnKeyDown(wParam, lParam);
        return 0;

    case WM_LBUTTONDOWN:
        OnLeftMouseButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hWnd, &ps);
            OnPaint(ps.hdc);
            EndPaint(hWnd, &ps);
        }
        return 0;

    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;

    case WM_DESTROY:
        OnDestroy();
        break;
    }

    return DefWindowProc(hWnd_, message, wParam, lParam);
}


LRESULT CALLBACK Window::WindowProc(HWND hWnd_, UINT message, WPARAM wParam, LPARAM lParam)
{
    Window* pWin = NULL;

    if (message == WM_NCCREATE)
    {
        MDICREATESTRUCT* pMDIC = (MDICREATESTRUCT*) ((LPCREATESTRUCT) lParam)->lpCreateParams;
        pWin = (Window*) (pMDIC->lParam);

        SetWindowLongPtr(hWnd_, GWLP_USERDATA, (LONG_PTR)pWin);
    }
    else
    {
        pWin = (Window*)GetWindowLongPtr(hWnd_, GWLP_USERDATA);
    }

    if (pWin)
    {
        return pWin->WndProc(hWnd_, message, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hWnd_, message, wParam, lParam);
    }
}
