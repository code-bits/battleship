
#pragma once

#include "field.h"
#include "cell.h"


class Player
{
public:
    Player();
    void SendCheckToAdversary(CellCoord cc);
    void SendMissToAdversary(CellCoord cc);
    void SendHitToAdversary(CellCoord cc);
    void SendKillToAdversary(CellCoord cc);

    void SendReady();

    virtual void Move();
    virtual void Wait();

    void LinkAdversary(Player * p);
    
protected:
    virtual void CheckIfHit(CellCoord cc) = 0;
    virtual void ReceiveMiss(CellCoord cc) = 0;
    virtual void ReceiveHit(CellCoord cc) = 0;
    virtual void ReceiveKill(CellCoord cc) = 0;

    bool canMove;
    Player * adversary;
    Field personalField;
    Field adversaryField;
};


class LocalPlayer : public Player
{
public:
    const Field& GetField();

protected:
    Field field;

    virtual void CheckIfHit(CellCoord cc);
    virtual void ReceiveMiss(CellCoord cc);
    virtual void ReceiveHit(CellCoord cc);
    virtual void ReceiveKill(CellCoord cc);

};


class HumanPlayer : public LocalPlayer
{

};


class BotPlayer : public LocalPlayer
{
public:
    virtual void Move();

};


class RemotePlayer : public Player
{
private:
    virtual void CheckIfHit(CellCoord cc);
    virtual void ReceiveMiss(CellCoord cc);
    virtual void ReceiveHit(CellCoord cc);
    virtual void ReceiveKill(CellCoord cc);
};
