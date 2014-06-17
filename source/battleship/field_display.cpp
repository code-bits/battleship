
#include "field_display.h"
#include "../field_display/stdafx.h"

void DrawCell(HDC hdc, int value, int i, int j)
{
	int xLeft = i + FldAreaLeft;
	int yTop = j + FldAreaTop;

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
	Rectangle(hdc, xLeft, yTop, xLeft + CellWidth + 1, yTop + CellWidth + 1);
    DeleteObject(hBrush);
}


void DrawField(HDC hdc, int ** field_array)
{
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			DrawCell(hdc, field_array[i][j], i * CellWidth, j * CellWidth);
		}
	}
	return;
}


bool IsInArea(POINT point, RECT rect)
{
    if ((point.x > rect.left) && (point.x < rect.right) &&
        (point.y > rect.top) && (point.y < rect.bottom))
    {
        return true;
    } else 
		return false;
}


bool CheckCell(HWND hwnd, CellCoord cCoord, int ** field_array)
{
	int value = field_array[cCoord.row][cCoord.col];

	switch (value)
	{
		case 0:
			MessageBox(hwnd, L"You have missed the ship!", L"Miss", MB_OK);
			field_array[cCoord.row][cCoord.col] = 1;
			break;

		case 1:
			MessageBox(hwnd, L"This cell was already accessed.", L"Double Access", MB_OK);
			break;

		case 2:
			MessageBox(hwnd, L"The ship is on fire!", L"Hit", MB_OK);
			field_array[cCoord.row][cCoord.col] = 3;
			break;

		case 3:
			MessageBox(hwnd, L"This cell was already accessed.", L"Double Access", MB_OK);
			break;

		default:
			break;
	}

	HDC hdc = GetDC(hwnd);
	DrawCell(hdc, field_array[cCoord.row][cCoord.col], cCoord.row * CellWidth, cCoord.col * CellWidth);
	ReleaseDC(hwnd, hdc);

	return true;
}