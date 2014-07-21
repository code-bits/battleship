
#include "player.h"
#include "stdafx.h"


Player::Player()
{
    canMove = false;
    int rows[6] = {1,2,4,6,6,6};
    int cols[6] = {1,1,2,1,2,3};

    for (int i=0; i<6; ++i)
    {
        personalField.Set(CellCoord(rows[i], cols[i]), ALIVE);
    }
}


void Player::Move()
{
    canMove = true;
}


void Player::Wait()
{
    canMove = false;
}


bool Player::CanMove()
{
    return canMove;
}


void Player::CheckIfHit(CellCoord cc, Player * adversary, Game * game)
{
    Outcome result = personalField.CheckCell(cc);

    switch (result)
    {
    case HIT:
        personalField.Set(cc, DEAD);
        game->ReportHitTo(adversary, this, cc);
        break;

    case MISSED:
        personalField.Set(cc, MISS);
        game->ReportMissTo(adversary, this, cc);
        break;

    case KILLED:
        personalField.Set(cc, DEAD);
        game->ReportKillTo(adversary, this, cc);
        break;
    }
}


void Player::OnHit(CellCoord cc, Player * adversary, Game * game)
{
    adversaryField.Set(cc, DEAD);
}


void Player::OnMiss(CellCoord cc, Player * adversary, Game * game)
{
    adversaryField.Set(cc, MISS);
}


void Player::OnKill(CellCoord cc, Player * adversary, Game * game)
{
    adversaryField.Set(cc, DEAD);
    // adversaryField.SurroundKilled(cc);
}


void BotPlayer::Update(Player * adversary, Game * game)
{
    static int r = 0;
    static int c = 0;
    if (CanMove())
    {
        game->CheckCellOf(adversary, this, CellCoord(r, c));

        ++c;

        if (c > 9)
        {
            c = 0;
            ++r;
        }

        if (r > 9)
        {
            r = 0;
        }
    }
}


void RemotePlayer::CheckIfHit(CellCoord cc, Player * adversary, Game * game)
{
    std::cout << "Execute Remote check!\n";
    Message msg("check", cc);
    Service::Network()->Send(Message::Encode(msg));
}


void RemotePlayer::OnHit(CellCoord cc, Player * adversary, Game * game)
{
    Message msg("hit", cc);
    Service::Network()->Send(Message::Encode(msg));
}


void RemotePlayer::OnMiss(CellCoord cc, Player * adversary, Game * game)
{
    Message msg("miss", cc);
    Service::Network()->Send(Message::Encode(msg));
}


void RemotePlayer::OnKill(CellCoord cc, Player * adversary, Game * game)
{
    Message msg("kill", cc);
    Service::Network()->Send(Message::Encode(msg));
}
