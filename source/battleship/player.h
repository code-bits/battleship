
#pragma once

class Player
{
public:
	void SendCheckToAdversary(CellCoord cc);
	void SendMissToAdversary(CellCoord cc);
	void SendHitToAdversary(CellCoord cc);
	void SendKillToAdversary(CellCoord cc);

	void LinkAdversary(Player * p);
	
private:
	virtual void CheckIfHit(CellCoord cc) = 0;
	virtual void ReceiveMiss(CellCoord cc) = 0;
	virtual void ReceiveHit(CellCoord cc) = 0;
	virtual void ReceiveKill(CellCoord cc) = 0;

	bool canMove;
	Player * adversary;
};


class LocalPlayer
{
protected:
	Field field;

private:
	virtual void CheckIfHit(CellCoord cc);
	virtual void ReceiveMiss(CellCoord cc);
	virtual void ReceiveHit(CellCoord cc);
	virtual void ReceiveKill(CellCoord cc);

};


class HumanPlayer
{
private:
	virtual void CheckIfHit(CellCoord cc);
	virtual void ReceiveMiss(CellCoord cc);
	virtual void ReceiveHit(CellCoord cc);
	virtual void ReceiveKill(CellCoord cc);
};


class BotPlayer
{
public:
	virtual void SendCheckToAdversary(CellCoord cc);
	virtual void SendMissToAdversary(CellCoord cc);
	virtual void SendHitToAdversary(CellCoord cc);
	virtual void SendKillToAdversary(CellCoord cc);

private:
	virtual void CheckIfHit(CellCoord cc);
	virtual void ReceiveMiss(CellCoord cc);
	virtual void ReceiveHit(CellCoord cc);
	virtual void ReceiveKill(CellCoord cc);
};


class RemotePlayer
{
public:
	virtual void SendCheckToAdversary(CellCoord cc);
	virtual void SendMissToAdversary(CellCoord cc);
	virtual void SendHitToAdversary(CellCoord cc);
	virtual void SendKillToAdversary(CellCoord cc);

private:
	virtual void CheckIfHit(CellCoord cc);
	virtual void ReceiveMiss(CellCoord cc);
	virtual void ReceiveHit(CellCoord cc);
	virtual void ReceiveKill(CellCoord cc);
};
