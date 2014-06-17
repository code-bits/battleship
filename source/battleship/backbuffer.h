#pragma once

#include <windows.h>

class Backbuffer
{
public:
    Backbuffer();
    ~Backbuffer();

    void Init(HDC hDC, int w, int h);
    void FillWithColor(COLORREF color);
    void Present(HDC hDC);
    void Resize(int w, int h);

    HDC GetDC() { return hBackbufferDC; }

private:
    int width;
    int height;
    HDC hBackbufferDC;
    HBITMAP hBackbufferBMP;
    HBITMAP hOldBMP;
};

