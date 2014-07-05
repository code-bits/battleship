#pragma once
#include <array>
#include <list>

#include "cell.h"

class Field
{
public:
    Field();
    void Set(CellCoord, CellState);
    CellState Get(CellCoord);
    Outcome CheckCell(CellCoord);
    void KilledFromCell(CellCoord);
    const std::array<std::array<CellState, 10>, 10>& GetCells() const;
    bool IsValid();

private:    
    std::array<std::array<CellState, 10>, 10> cells;
    bool IsCellKilled(CellCoord cc);
    std::list<CellCoord> GetNeighbours(CellCoord);

    int CountNeighbours(std::array<std::array<CellState, 10>, 10> array, int i, int j);
};
