
#include "game.h"
#include "stdafx.h"


Game::Game(Player * main, Player * adversary)
{
    mainPlayer = main;
    adversaryPlayer = adversary;
    state = new InitialGameState();
}


Game::~Game()
{
    if (state) { delete state; }
}


void Game::PrepareStart()
{
    delete state;
    state = new TransitionGameState();
}

void Game::Start()
{
    std::cout << "Start!\n";
    delete state;
    state = new ActiveGameState();
    mainPlayer->Move();
}


void Game::HandleInput(const MSG & msg)
{
    state->HandleInput(msg, this);
}

void Game::Update()
{
    state->Update(this);
}

void Game::Draw(HDC hDC)
{
    state->Draw(hDC, this);
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


void Game::DispatchActions()
{
    while (!actions.empty())
    {
        Action::ActionBase * action = actions.front();
        actions.pop();
        action->Execute(this);
        delete action;
    }
}


Player * Game::MainPlayer()
{
    return mainPlayer;
}


Player * Game::AdversaryPlayer()
{
    return adversaryPlayer;
}


ActiveGameState::ActiveGameState()
{
    mainDisplayParams.x = 20;
    mainDisplayParams.y = 20;
    mainDisplayParams.cx = 140;
    mainDisplayParams.cy = 140;

    adversaryDisplayParams.x = 180;
    adversaryDisplayParams.y = 20;
    adversaryDisplayParams.cx = 400;
    adversaryDisplayParams.cy = 400;
}


void ActiveGameState::HandleInput(const MSG & msg, Game * game)
{
    switch (msg.message)
    {
    case WM_LBUTTONDOWN:
        {
            std::cout << "Click!\n";
            int x = GET_X_LPARAM(msg.lParam);
            int y = GET_Y_LPARAM(msg.lParam);
            CellCoord cc;

            if (game->MainPlayer()->adversaryField.Click(x, y, adversaryDisplayParams, &cc))
            {
                if (game->MainPlayer()->CanMove())
                {
                    std::cout << "Move " << cc.row << " " << cc.col << std::endl;
                    game->CheckCellOf(game->AdversaryPlayer(), game->MainPlayer(), cc);
                }
            }
        }
        break;
    }
}


void ActiveGameState::Update(Game * game)
{
    game->DispatchActions();
    game->AdversaryPlayer()->Update(game->MainPlayer(), game);
}


void ActiveGameState::Draw(HDC hDC, Game * game)
{
    game->MainPlayer()->personalField.Draw(hDC, mainDisplayParams);
    game->MainPlayer()->adversaryField.Draw(hDC, adversaryDisplayParams);
}


InitialGameState::InitialGameState()
{
    mainDisplayParams.x = 180;
    mainDisplayParams.y = 20;
    mainDisplayParams.cx = 400;
    mainDisplayParams.cy = 400;
}


void InitialGameState::HandleInput(const MSG & msg, Game * game)
{
    switch (msg.message)
    {
    case WM_LBUTTONDOWN:
        {
            std::cout << "Click!\n";
            int x = GET_X_LPARAM(msg.lParam);
            int y = GET_Y_LPARAM(msg.lParam);
            CellCoord cc;
            if (game->MainPlayer()->personalField.Click(x, y, mainDisplayParams, &cc))
            {
                game->MainPlayer()->personalField.Set(cc, ALIVE);
            }
        }
        break;
    }
}


void InitialGameState::Draw(HDC hDC, Game * game)
{
    game->MainPlayer()->personalField.Draw(hDC, mainDisplayParams);
}


TransitionGameState::TransitionGameState()
{
    currentIteration = 0;
    iterations = 30;

    mainIn.x = 180;
    mainIn.y= 20;
    mainIn.cx = 400;
    mainIn.cy = 400;

    mainOut.x = 20;
    mainOut.y = 20;
    mainOut.cx = 140;
    mainOut.cy = 140;

    advIn.x = 580;
    advIn.y = 20;
    advIn.cx = 0;
    advIn.cy = 400;

    advOut.x = 180;
    advOut.y = 20;
    advOut.cx = 400;
    advOut.cy = 400;
}

void TransitionGameState::Update(Game * game)
{
    float ratio = (float)currentIteration/(float)iterations;

    mainCurr.x = (mainOut.x - mainIn.x) * ratio + mainIn.x;
    mainCurr.y = (mainOut.y - mainIn.y) * ratio + mainIn.y;
    mainCurr.cx = (mainOut.cx - mainIn.cx) * ratio + mainIn.cx;
    mainCurr.cy = (mainOut.cy - mainIn.cy) * ratio + mainIn.cy;

    advCurr.x = (advOut.x - advIn.x) * ratio + advIn.x;
    advCurr.y = (advOut.y - advIn.y) * ratio + advIn.y;
    advCurr.cx = (advOut.cx - advIn.cx) * ratio + advIn.cx;
    advCurr.cy = (advOut.cy - advIn.cy) * ratio + advIn.cy;

    if (currentIteration < iterations)
    {
        ++currentIteration;
    }
    else
    {
        game->Start();
    }
}


void TransitionGameState::Draw(HDC hDC, Game * game)
{
    game->MainPlayer()->personalField.Draw(hDC, mainCurr);
    game->MainPlayer()->adversaryField.Draw(hDC, advCurr);
}
