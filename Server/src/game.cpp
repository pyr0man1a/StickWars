
#include "game.h"
#include "Map.h"
#include "MapBuilder.h"
#include "player.h"

#include "packets/action.h"
#include "packets/entity_update.h"
#include "packets/game_over.h"
#include "packets/player_defeated.h"
#include "packets/player_definition.h"
#include "packets/player_update.h"
#include "packets/post_game.h"
#include "packets/turn_change.h"

CGame::CGame(uint8 map, std::vector<CPlayer*> playerList)
{
	m_playerList = playerList;
	MapBuilder *builder = new MapBuilder(map, playerList);
	m_map = builder->getResult();
	m_activePlayer = 0;
	m_winner = NULL;
}

CGame::~CGame()
{
	delete m_map;
}

Map* CGame::getMap()
{
	return m_map;
}

Unit* CGame::getUnit(uint16 id)
{
	return m_map->getUnit(id);
}

void CGame::endTurn()
{
	m_activePlayer = m_activePlayer >= m_playerList.size() - 1 ? 0 : m_activePlayer + 1;

	CPlayer* active = m_playerList[m_activePlayer];

	active->AddMoney(active->GetIncome());

	active->pushPacket(new CPlayerUpdatePacket(active));

	for (auto player : m_playerList)
	{
		player->pushPacket(new CTurnChangePacket(m_activePlayer));
	}
}

void CGame::start()
{
	m_activePlayer = 0;

	for (auto player : m_playerList)
	{
		for (uint8 i = 0; i < m_playerList.size(); i++)
		{
			player->pushPacket(new CPlayerDefinitionPacket(m_playerList[i], i));
		}
		if (player == m_playerList[m_activePlayer])
		{
			CPlayer* active = m_playerList[m_activePlayer];

			active->AddMoney(active->GetIncome());

			active->pushPacket(new CPlayerUpdatePacket(active));
		}
		player->pushPacket(new CTurnChangePacket(m_activePlayer));
	}
}

void CGame::addPlayer(CPlayer* player)
{
	player->SetMoney(0);
	player->SetScore(0);
	player->SetIncome(2000);
}

void CGame::end(CPlayer* winner)
{
	m_winner = winner;

	for (auto p : m_playerList)
	{
		p->pushPacket(new CGameOverPacket(winner, getPlayerNumber(winner)));
		p->pushPacket(new CPostGamePacket(winner, this));

		if (p == m_winner)
		{
			p->AddWin();
		}
		else
		{
			p->AddLoss();
		}
	}
}

bool CGame::hasPlayer(CPlayer* player)
{
	for (auto p : m_playerList)
	{
		if (p->id == player->id)
		{
			return true;
		}
	}
	return false;
}

bool CGame::isActivePlayer(CPlayer* player)
{
	return player == m_playerList.at(m_activePlayer);
}

uint8 CGame::getActivePlayer()
{
	return m_activePlayer;
}

bool CGame::isWinner(CPlayer* player)
{
	return player == m_winner;
}

void CGame::updateEntity(Unit* unit)
{
	for (auto p : m_playerList)
	{
		p->pushPacket(new CEntityUpdatePacket(unit, m_map->getUnitPos(unit->getID())));
	}
}

void CGame::checkVictoryCondition()
{
	int losers = 0;
	for (auto p : m_playerList)
	{
		if (!m_map->unitsRemain(p))
		{
			losers++;
		}
	}
	if (losers == m_playerList.size() - 1)
	{
		for (auto p : m_playerList)
		{
			if (m_map->unitsRemain(p))
			{
				end(p);
			}
		}
	}
	delete this;
}

void CGame::sendAction(Unit* initiator, Unit* target, ACTION action, int8 dmginit, int8 dmgtarget, std::pair<uint8, uint8> pos)
{
	for (auto p : m_playerList)
	{
		p->pushPacket(new CActionPacket(initiator, target, action, dmginit, dmgtarget, pos));
	}
}

uint8 CGame::getPlayerNumber(CPlayer* player)
{
	for (uint8 i = 0; i < m_playerList.size(); i++)
	{
		if (m_playerList[i] == player)
		{
			return i;
		}
	}
	return -1;
}

void CGame::playerDefeated(CPlayer* player)
{
	for (auto p : m_playerList)
	{
		p->pushPacket(new CPlayerDefeatedPacket(player, getPlayerNumber(player)));
	}
}

namespace games
{
	std::vector<CGame*> gameList;

	CGame* createGame(uint8 mapID, std::vector<CPlayer*> playerList)
	{
		CGame* game = new CGame(mapID, playerList);
		gameList.push_back(game);
		return game;
	}

	CGame* getGame(CPlayer* player)
	{
		for (auto game : gameList)
		{
			if (game->hasPlayer(player))
			{
				return game;
			}
		}
		return NULL;
	}
}
