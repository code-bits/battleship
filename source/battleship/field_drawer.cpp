#include "field_drawer.h"
#include "stdafx.h"

FieldDrawer::FieldDrawer(int top, int left, int size)
	: top(top),
	  left(left)
{
	cellSize = size/10;
}

void FieldDrawer::Draw(HDC hdc, const std::array<std::array<CellState, 10>, 10>& cells)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			DrawCell(hdc, cells[i][j], i * cellSize, j * cellSize);
		}
	}
	return;
}


void FieldDrawer::DrawCell(HDC hdc, CellState value, int iy, int jx)
{
	int xLeft = jx + left;
	int yTop = iy + top;

	COLORREF color;

	switch (value)
	{
		case 0:
			color = RGB(10, 25, 75);
			break;

		case 1:
			color = RGB(50, 75, 110);
			break;

		case 2:
			color = RGB(250, 250, 10);
			break;

		case 3:
			color = RGB(255, 50, 10);
			break;

		default:
			color = RGB(255, 250, 250);
			break;
	}

	HBRUSH hBrush = CreateSolidBrush(color);
	HPEN strokePen = CreatePen(PS_SOLID, 1, RGB(100, 100, 100));
	SelectObject(hdc, strokePen);
    SelectObject(hdc, hBrush);
	Rectangle(hdc, xLeft, yTop, xLeft + cellSize + 1, yTop + cellSize + 1);
    DeleteObject(hBrush);
	DeleteObject(strokePen);
}
