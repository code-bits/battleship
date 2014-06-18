#include "field.h"
#include "stdafx.h"


CellState Field::Get(CellCoord cc)
{
	return cells[cc.row][cc.col];
}

void Field::Set(CellCoord cc, CellState value)
{
	 cells[cc.row][cc.col] = value;
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