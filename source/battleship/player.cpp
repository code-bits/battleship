
#include "player.h"
#include "stdafx.h"


Player::Player()
{
    canMove = false;
    adversary = NULL;
}


void Player::Move()
{
    canMove = true;
}


void Player::Wait()
{
    canMove = false;
}


void Player::LinkAdversary(Player * p)
{
    adversary = p;
}


void Player::SendCheckToAdversary(CellCoord cc)
{
    if (canMove)
    {
        adversary->CheckIfHit(cc);
    }
}


void Player::SendHitToAdversary(CellCoord cc)
{
    adversary->ReceiveHit(cc);
}


void Player::SendMissToAdversary(CellCoord cc)
{
    adversary->ReceiveMiss(cc);
}


void Player::SendKillToAdversary(CellCoord cc)
{
    adversary->ReceiveKill(cc);
}


void LocalPlayer::CheckIfHit(CellCoord cc)
{
    Outcome result = personalField.CheckCell(cc);

    switch (result)
    {
    case HIT:
        personalField.Set(cc, DEAD);
        SendHitToAdversary(cc);
        break;

    case MISSED:
        personalField.Set(cc, MISS);
        SendMissToAdversary(cc);
        break;

    case KILLED:
        personalField.Set(cc, DEAD);
        SendKillToAdversary(cc);
        break;
    }
}


void LocalPlayer::ReceiveHit(CellCoord cc)
{
    adversaryField.Set(cc, DEAD);
    Move();
}


void LocalPlayer::ReceiveMiss(CellCoord cc)
{
    adversaryField.Set(cc, MISS);
    Wait();
    adversary->Move();
}


void LocalPlayer::ReceiveKill(CellCoord cc)
{
    // adversaryField.SurroundKilled(cc);
    Move();
}


void BotPlayer::Move()
{
    canMove = true;
}


