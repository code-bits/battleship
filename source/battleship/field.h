#pragma once
#include <array>
#include <list>

#include "cell.h"

struct FieldDisplayParams
{
    int x;
    int y;
    int size;
};

class Field
{
public:
    Field();
    void Set(CellCoord cc, CellState state);
    CellState Get(CellCoord cc);
    Outcome CheckCell(CellCoord cc);
    void KilledFromCell(CellCoord cc);
    const std::array<std::array<CellState, 10>, 10>& GetCells() const;
    bool IsValid();
    void Draw(HDC hDC, const FieldDisplayParams & fdp);
    bool Click(int x, int y, const FieldDisplayParams & fdp, CellCoord * cc);

private:
    std::array<std::array<CellState, 10>, 10> cells;
    bool IsCellKilled(CellCoord cc);
    std::list<CellCoord> GetNeighbours(CellCoord cc);

    int CountNeighbours(std::array<std::array<CellState, 10>, 10> array, int i, int j);
    bool IsInArea(int x, int y);
};
