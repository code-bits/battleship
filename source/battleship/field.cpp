#include "field.h"
#include "stdafx.h"



Field::Field()
{
	for (unsigned short i=0; i<10; ++i)
	{
		for (unsigned short j=0; j<10; ++j)
		{
			cells[i][j] = BLANK;
		}
	}	
}


CellState Field::Get(CellCoord cc)
{
	return cells[cc.row][cc.col];
}


void Field::Set(CellCoord cc, CellState value)
{
	 cells[cc.row][cc.col] = value;
}


std::array<std::array<CellState, 10>, 10> Field::GetCells()
{
	return cells;
}


Outcome Field::CheckCell(CellCoord cc)
{
	if (cells[cc.row][cc.col] == BLANK || cells[cc.row][cc.col] == MISS)
	{
		return MISSED;
	}

	if (cells[cc.row][cc.col] == ALIVE && IsCellKilled(cc))
	{
		return KILLED;
	}
	return HIT;
}


std::list<CellCoord> Field::GetNeighbours(CellCoord target)
{
	std::list<CellCoord> neighbours;
	CellCoord temp;
	int x = target.row;
	int y = target.col;

	if(x > 0 && y >= 0)			//not leftmost column
	{
		temp.col = y;
		temp.row = x - 1;
		neighbours.push_front(temp);
	}
	if(x < 9 && y >= 0)			//not rightmost column
	{
		temp.col = y;
		temp.row = x + 1;
		neighbours.push_front(temp);
	}
	if(x >= 0 && y > 0)			//not uppermost row
	{
		temp.col = y - 1;
		temp.row = x;
		neighbours.push_front(temp);
	}
	if(x >= 0 && y < 9)			//not downmost row
	{
		temp.col = y + 1;
		temp.row = x;
		neighbours.push_back(temp);
	}
	return neighbours;
}

bool Field::IsCellKilled(CellCoord cc)
{
	std::list<CellCoord> to_check, checked;

	to_check.push_back(cc);

	while (!to_check.empty())
	{
		CellCoord target = to_check.front();
		to_check.pop_front();
		checked.push_back(target);

		std::list<CellCoord> neighbours = GetNeighbours(target);

		std::list<CellCoord>::iterator itr;

		for (itr = neighbours.begin(); itr != neighbours.end(); ++itr)
		{
			switch (cells[(*itr).row][(*itr).col])
			{
			case ALIVE:
				return true;
				break;

			case DEAD:
				{
					std::list<CellCoord>::iterator res = std::find(checked.begin(), checked.end(), *itr);
					if (res != checked.end())
					{
						to_check.push_back(*res);
					}
				}
				break;

			default:
				break;
			}
		}		
	}

	
	return false;

}

bool Field::IsValid()
{
	int ships[4];
	int iCurrent = 0;
	bool isValid = true;
	CellCoord cc;

	for (int i = 0; i < 4; i++) ships[i] = 0;

	std::array<std::array <CellState, 10>, 10> inCells;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cc.row = i;
			cc.col = j;

			if(Get(cc) == BLANK)
			{
				inCells[i][j] = BLANK;
			} else
			{
				inCells[i][j] = MISS;
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (inCells[i][j])
			{
				iCurrent = 0;
				iCurrent += CountNeighbours(inCells, i, j);

				if(iCurrent > 0)
					++ships[iCurrent - 1];
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		std::cout << "Ships of " << (i + 1) << " elements:" << ships[i] << std::endl;

		if(ships[i] != (4 - i))
			isValid = false;
	}

	return isValid;
}


int Field::CountNeighbours(std::array<std::array<CellState, 10>, 10> array, int i, int j)
{
	if(array[i][j] == BLANK) return 0;

	int result = 1;

	array[i][j] = BLANK;

	if(i > 0) 
		result += CountNeighbours(array, i-1, j);
	if(j > 0)
		result += CountNeighbours(array, i, j-1);
	if(i < 9)
		result += CountNeighbours(array, i+1, j);
	if(j < 9)
		result += CountNeighbours(array, i, j+1);

	return result;
}

