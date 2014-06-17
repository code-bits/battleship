#include "field.h"
#include "stdafx.h"


CellState Field::Get(int x, int y)
{
	return cells[x][y];
}

void Field::Set(int x, int y, CellState value)
{
	 cells[x][y] = value;
}
