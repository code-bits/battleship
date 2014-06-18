#pragma once
#include <array>

#include "cell.h"

class Field
{
public:
	Field();
	void Set(CellCoord, CellState);
	CellState Get(CellCoord);
	Outcome CheckCell(CellCoord);
	std::array<std::array<CellState, 10>, 10> GetCells();

private:
	std::array<std::array<CellState, 10>, 10> cells;
	bool IsCellKilled(CellCoord cc);
	std::list<CellCoord> GetNeighbours(CellCoord);

};
