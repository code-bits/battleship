#pragma once


class FieldDrawer
{
public:
    FieldDrawer(int top, int left, int size);
    void Draw(HDC hdc, const std::array<std::array<CellState, 10>, 10>& cells);
    void DrawCell(HDC hdc, CellState value, int i, int j);
private:
    int top;
    int left;
    int cellSize;
};
