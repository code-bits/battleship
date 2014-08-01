
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
    Game(Player * main, Player * adversary);
    ~Game();

    void HandleInput(const MSG & msg);
    void Update();
    void Draw(HDC hDC);

    void PrepareStart();
    void Start();

    void CheckCellOf(Player * target, Player * origin, CellCoord cc);
    void ReportMissTo(Player * target, Player * origin, CellCoord cc);
    void ReportHitTo(Player * target, Player * origin, CellCoord cc);
    void ReportKillTo(Player * target, Player * origin, CellCoord cc);

    void DispatchActions();

    Player * MainPlayer();
    Player * AdversaryPlayer();

private:
    std::queue<Action::ActionBase*> actions;
    GameState * state;

    Player * mainPlayer;
    Player * adversaryPlayer;
};


class GameState
{
public:
    virtual void HandleInput(const MSG & msg, Game * game) { }
    virtual void Update(Game * game) { }
    virtual void Draw(HDC hDC, Game * game) { }
};


class ActiveGameState : public GameState
{
public:
    ActiveGameState();
    virtual void HandleInput(const MSG & msg, Game * game);
    virtual void Update(Game * game);
    virtual void Draw(HDC hDC, Game * game);
private:
    FieldDisplayParams mainDisplayParams;
    FieldDisplayParams adversaryDisplayParams;
};


class InitialGameState : public GameState
{
public:
    InitialGameState();
    virtual void HandleInput(const MSG & msg, Game * game);
    virtual void Draw(HDC hDC, Game * game);
private:
    FieldDisplayParams mainDisplayParams;
};


class TransitionGameState : public GameState
{
public:
    TransitionGameState();
    virtual void Update(Game * game);
    virtual void Draw(HDC hDC, Game * game);
private:
    int currentIteration;
    int iterations;
    FieldDisplayParams mainIn;
    FieldDisplayParams mainOut;
    FieldDisplayParams advIn;
    FieldDisplayParams advOut;

    FieldDisplayParams mainCurr;
    FieldDisplayParams advCurr;
};

