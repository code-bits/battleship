#pragma once

struct CellCoord
{
    int row;
    int col;

    CellCoord() : row(0), col(0) { }
    CellCoord(int r, int c) : row(r), col(c) { }

    bool operator==(CellCoord cc)
    {
        return row == cc.row && col == cc.col;
    }
};



enum CellState
{
    BLANK,
    MISS,
    ALIVE,
    DEAD
};

enum Outcome
{
    HIT,
    MISSED,
    KILLED
};
