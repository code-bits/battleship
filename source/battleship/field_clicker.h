#pragma once

class FieldClicker
{
public:
    FieldClicker(int top, int left, int fieldSize);
    bool CheckClick(int x, int y, CellCoord * cc);

private:
    int top;
    int left;
    int size;

    bool IsInArea(int x, int y);
};
