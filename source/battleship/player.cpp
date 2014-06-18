
#include "player.h"
#include "stdafx.h"


void Player::SendCheckToAdversary(CellCoord cc)
{
	if (mayMove)
	{
		adversary->CheckIfHit(cc);
	}	
}


void Player::SendHitToAdversary(CellCoord cc)
{
	adversary->SendHitToAdversary(cc);
}


void Player::SendMissToAdversary(CellCoord cc)
{
	adversary->SendMissToAdversary(cc);
}


void Player::SendKillToAdversary(CellCoord cc)
{
	adversary->SendKillToAdversary(cc);
}


void LocalPlayer::CheckIfHit(CellCoord cc)
{
	Outcome result = field.CheckCell(cc);

	switch (result)
	{
		case HIT;
			field.Set(cc, DEAD);
			SendHitToAdversary(cc);
			adversary->ReceiveHit(cc);
			break;

		case MISSED:
			field.Set(cc, MISS);
			SendMissToAdversary(cc);
			break;

		case KILLED:
			field.Set(cc, DEAD);
			SendKillToAdversary(cc);
			break;
	}
}


void LocalPlayer::ReceiveHit(CellCoord cc)
{
	// change adversary field
	canMove = true;
}


void LocalPlayer::ReceiveMiss(CellCoord cc)
{
	// change adversary field
	canMove = false;
}


void LocalPlayer::ReceiveKill(CellCoord cc)
{
	// change adversary field
	canMove = true;
}
