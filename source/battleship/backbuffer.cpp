
#include "backbuffer.h"
#include "stdafx.h"


Backbuffer::Backbuffer()
{
    hBackbufferDC = NULL;
    hBackbufferBMP = NULL;
    width = 0;
    height = 0;
}


Backbuffer::~Backbuffer()
{
    SelectObject(hBackbufferDC, hOldBMP);
    if (hBackbufferBMP) { DeleteObject(hBackbufferBMP); }
    if (hBackbufferDC) { DeleteDC(hBackbufferDC); }
}


void Backbuffer::Init(HDC hDC, int w, int h)
{
    width = (w < 1) ? 1 : w;
    height = (h < 1) ? 1 : h;

    hBackbufferDC = CreateCompatibleDC(hDC);
    hBackbufferBMP = CreateCompatibleBitmap(hDC, width, height);

    hOldBMP = (HBITMAP)SelectObject(hBackbufferDC, hBackbufferBMP);
}


void Backbuffer::FillWithColor(COLORREF color)
{
    HBRUSH hColorBr = CreateSolidBrush(color);
    HPEN hColorPen = CreatePen(PS_SOLID, 1, color);

    HBRUSH hOldBr = (HBRUSH)SelectObject(hBackbufferDC, hColorBr);
    HPEN hOldPen = (HPEN)SelectObject(hBackbufferDC, hColorPen);

    Rectangle(hBackbufferDC, 0, 0, width, height);

    DeleteObject(SelectObject(hBackbufferDC, hOldPen));
    DeleteObject(SelectObject(hBackbufferDC, hOldBr));
}


void Backbuffer::Resize(int w, int h)
{
    width = (w < 1) ? 1 : w;
    height = (h < 1) ? 1 : h;

    hBackbufferBMP = CreateCompatibleBitmap(hBackbufferDC, width, height);
    DeleteObject(SelectObject(hBackbufferDC, hBackbufferBMP));
}


void Backbuffer::Present(HDC hDC)
{
    BitBlt(hDC, 0, 0, width, height, hBackbufferDC, 0, 0, SRCCOPY);
}

