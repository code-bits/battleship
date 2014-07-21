
#include "game.h"
#include "stdafx.h"

void Game::Update()
{
    while (!actions.empty())
    {
        Action::ActionBase * action = actions.front();
        actions.pop();
        action->Execute(this);
        delete action;
    }
}



void Game::CheckCellOf(Player * target, Player * origin, CellCoord cc)
{
    actions.push(new Action::CheckCellOf(target, origin, cc));
}


void Game::ReportHitTo(Player * target, Player * origin, CellCoord cc)
{
    actions.push(new Action::ReportHitTo(target, origin, cc));
}


void Game::ReportMissTo(Player * target, Player * origin, CellCoord cc)
{
    actions.push(new Action::ReportMissTo(target, origin, cc));
}


void Game::ReportKillTo(Player * target, Player * origin, CellCoord cc)
{
    actions.push(new Action::ReportKillTo(target, origin, cc));
}
