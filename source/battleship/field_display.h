
#pragma once

#include <windows.h>
#include "message.h"

#define Rows				10
#define Columns				10

#define CellWidth			25

#define FldAreaTop			25
#define FldAreaLeft			200
#define FldAreaBtm (Rows * CellWidth + FldAreaTop)
#define FldAreaRgt (Columns * CellWidth + FldAreaLeft)

void DrawCell(HDC hdc, int value, int i, int j);

void DrawField(HDC hdc, const std::array<std::array<CellState, 10>, 10>& cells);

bool IsInArea(POINT point, RECT rect);

bool MyCheckCell(HWND hwnd, CellCoord cCoord, int ** field_array);