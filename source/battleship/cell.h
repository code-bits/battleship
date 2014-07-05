#pragma once

struct CellCoord
{
    int row;
    int col;

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
