#include "field.h"

CellState Field::Get(int x, int y)
{
	return field[x][y-1];
}

void Field::Set(int x, int y, CellState value)
{
	 field[x][y]=value;
}

bool Field::IsVisible(int x, int y)
{
	return visibility[x][y];
}