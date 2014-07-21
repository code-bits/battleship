
#pragma once

#include <queue>

namespace Action
{
    class ActionBase;
}

class Player;

class GameState;

class Game
{
public:
    void Update();
    void Draw();

    void CheckCellOf(Player * target, Player * origin, CellCoord cc);
    void ReportMissTo(Player * target, Player * origin, CellCoord cc);
    void ReportHitTo(Player * target, Player * origin, CellCoord cc);
    void ReportKillTo(Player * target, Player * origin, CellCoord cc);

private:
    std::queue<Action::ActionBase*> actions;
    GameState * state;
};
