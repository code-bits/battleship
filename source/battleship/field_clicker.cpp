#include "field_clicker.h"
#include "stdafx.h"

FieldClicker::FieldClicker(int t, int l, int s)
	: top(t),
	  left(l)
{
	size = (s/10);
}


bool FieldClicker::CheckClick(int x, int y, CellCoord * cc)
{
	if (IsInArea(x, y))
	{
		cc->col = (x - left)/10;
		cc->row = (y - top)/10;
		return true;
	}
	else
	{
		return false;
	}	
}


bool FieldClicker::IsInArea(int x, int y)
{
	if (x >= left && x < left + size
		&& y >= top && y < top + size)
	{
		return true;
	}
	
	return false;
}
