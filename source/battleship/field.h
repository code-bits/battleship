#pragma once

#include "cell.h"

class Field
{
private:
	CellState cells[10][10];

public:
	void Set(CellCoord cc, CellState cs);
	CellState Get(CellCoord);
	bool IsVisible(CellCoord);
	Outcome CheckCell(CellCoord);
	bool IsCellKilled(CellCoord cc);
	std::list<CellCoord> GetNeighbours(CellCoord);
};