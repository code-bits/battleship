#pragma once

enum CellState
{
	BLANK,
	MISS,
	ALIVE,
	DEAD,
};

class Field
{
private:
	CellState cells[10][10];

public:
	void Set(int, int, CellState);
	CellState Get(int, int);
	bool IsVisible(int, int);

};
