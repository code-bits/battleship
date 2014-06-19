#pragma once

#include <windows.h>
#include "message.h"



bool IsInArea(POINT point, RECT rect);

bool MyCheckCell(HWND hwnd, CellCoord cCoord, int ** field_array);