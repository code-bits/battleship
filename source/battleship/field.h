#pragma once

enum CellState
{
	blankHit,
	blankUnHit,
	shipHit,
	shipUnHit,
};

class Field
{
private:
	CellState field[10][10];
	bool visibility[10][10];
public:
	void Set(int, int, CellState);
	CellState Get(int, int);
	bool IsVisible(int, int);
};