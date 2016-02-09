#include "player.h"
#include "server.h"
#include "packets/packet.h"

CPlayer::CPlayer(int id)
{
	this->id = id;
	m_wins = 0;
	m_losses = 0;
	m_team = 0;
	m_color = 0;
	m_money = 0;
	m_score = 0;
	m_income = 0;
}

CPlayer::~CPlayer()
{

}

const char* CPlayer::GetName()
{
	return m_username.c_str();
}

void CPlayer::SetName(const char* name)
{
	m_username.clear();
	m_username.append(name);
}

void CPlayer::SetWins(uint32 wins)
{
	m_wins = wins;
}

void CPlayer::SetLosses(uint32 losses)
{
	m_losses = losses;
}

void CPlayer::AddWin()
{
	m_wins++;

	char* query = "UPDATE accounts SET wins = %d WHERE id = %d;";

	Sql_Query(SqlHandle, query, m_wins, id);
}

void CPlayer::AddLoss()
{
	m_losses++;

	char* query = "UPDATE accounts SET losses = %d WHERE id = %d;";

	Sql_Query(SqlHandle, query, m_losses, id);
}

void CPlayer::SetTeam(uint8 team)
{
	m_team = team;
}

void CPlayer::SetColor(uint8 color)
{
	m_color = color;
}

void CPlayer::SetMoney(int32 money)
{
	m_money = money;
}

void CPlayer::AddMoney(int32 money)
{
	m_money += money;
}

void CPlayer::SetScore(int32 score)
{
	m_score = score;
}

void CPlayer::AddScore(int32 score)
{
	m_score += score;
}

void CPlayer::SetIncome(int32 income)
{
	m_income = income;
}

void CPlayer::AddIncome(int32 income)
{
	m_income += income;
}

uint32 CPlayer::GetWins()
{
	return m_wins;
}

uint32 CPlayer::GetLosses()
{
	return m_losses;
}

uint8 CPlayer::GetTeam()
{
	return m_team;
}

uint8 CPlayer::GetColor()
{
	return m_color;
}

int32 CPlayer::GetMoney()
{
	return m_money;
}

int32 CPlayer::GetIncome()
{
	return m_income;
}

int32 CPlayer::GetScore()
{
	return m_score;
}

bool CPlayer::packetQueueEmpty()
{
	return PacketQueue.empty();
}
void CPlayer::clearPacketQueue()
{
	while (!packetQueueEmpty())
	{
		delete popPacket();
	}
}
void CPlayer::pushPacket(CPacket* packet)
{
	PacketQueue.push_back(packet);
}
CPacket* CPlayer::popPacket()
{
	CPacket* PPacket = PacketQueue.front();
	PacketQueue.pop_front();
	return PPacket;
}