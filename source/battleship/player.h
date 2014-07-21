
#pragma once

#include "field.h"
#include "cell.h"

class Game;

class Player
{
public:
    Player();

    void Move();
    void Wait();
    bool CanMove();

    virtual void CheckIfHit(CellCoord cc, Player * adversary, Game * game);
    virtual void OnMiss(CellCoord cc, Player * adversary, Game * game);
    virtual void OnHit(CellCoord cc, Player * adversary, Game * game);
    virtual void OnKill(CellCoord cc, Player * adversary, Game * game);

    Field personalField;
    Field adversaryField;

protected:

    bool canMove;
};


class BotPlayer : public Player
{
public:
    virtual void Update(Player * adversary, Game * game);
};

class RemotePlayer : public Player
{
    virtual void CheckIfHit(CellCoord cc, Player * adversary, Game * game);
    virtual void OnMiss(CellCoord cc, Player * adversary, Game * game);
    virtual void OnHit(CellCoord cc, Player * adversary, Game * game);
    virtual void OnKill(CellCoord cc, Player * adversary, Game * game);
};
