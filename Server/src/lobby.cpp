
#include "lobby.h"
#include "player.h"
#include "game.h"

#include "packets/game_load.h"
#include "packets/lobby_update.h"
#include "packets/lobby_countdown.h"

CLobby::CLobby(uint32 id)
{
	this->id = id;
	m_maxSize = 2;
	m_mapID = 0;
}

CLobby::~CLobby()
{

}

uint8 CLobby::getMaxSize()
{
	return m_maxSize;
}

void CLobby::setMapID(uint8 map)
{
	m_mapID = map;
}

void CLobby::setHost(CPlayer* host)
{
	m_Host = host;
}

CPlayer* CLobby::getHost()
{
	return m_Host;
}

uint8 CLobby::getMapID()
{
	return m_mapID;
}

void CLobby::addPlayer(CPlayer* player)
{
	playerList.push_back(player);
	uint8 number = playerNumber(player);
	player->SetColor(number);
	player->SetTeam(number);

	for (auto p : playerList)
	{
		p->pushPacket(new CLobbyUpdatePacket(this));
	}
}

void CLobby::removePlayer(CPlayer* player)
{
	for (uint8 i = 0; i < playerList.size(); i++)
	{
		if (playerList.at(i)->id == player->id)
		{
			playerList.erase(playerList.begin() + i);
		}
	}
	for (auto p : playerList)
	{
		uint8 number = playerNumber(p);
		p->SetColor(number);
		p->SetTeam(number);
	}
	for (auto p : playerList)
	{
		p->pushPacket(new CLobbyUpdatePacket(this));
	}
}

bool CLobby::hasPlayer(CPlayer* player)
{
	for (auto p : playerList)
	{
		if (p->id == player->id)
		{
			return true;
		}
	}
	return false;
}

uint8 CLobby::playerNumber(CPlayer* player)
{
	for (uint8 i = 0; i < playerList.size(); i++)
	{
		if (playerList.at(i)->id == player->id)
		{
			return i;
		}
	}
	return -1;
}

LOBBYSTATUS CLobby::getStatus()
{
	return m_status;
}

void CLobby::startCountdown()
{
	m_status = LOBBY_STARTING;
	m_lastCountdown = 5;

	for (auto player : playerList)
	{
		player->pushPacket(new CLobbyCountdownPacket(5));
	}
}

void CLobby::cancelCountdown()
{
	m_status = LOBBY_IDLE;
	m_lastCountdown = 0;

	for (auto player : playerList)
	{
		player->pushPacket(new CLobbyCountdownPacket(0));
	}
}

uint8 CLobby::nextTick()
{
	return m_lastCountdown == 0 ? 0 : --m_lastCountdown;
}

namespace lobbies
{
	std::vector<CLobby*> lobbyList;

	std::vector<CLobby*> getLobbies()
	{
		return lobbyList;
	}

	CLobby* createLobby()
	{
		CLobby* lobby = new CLobby(newLobbyId());
		lobbyList.push_back(lobby);
		return lobby;
	}

	CLobby* getLobby(CPlayer* player)
	{
		for (auto lobby : lobbyList)
		{
			if (lobby->hasPlayer(player))
			{
				return lobby;
			}
		}
		return NULL;
	}

	CLobby* getLobby(uint32 id)
	{
		for (auto lobby : lobbyList)
		{
			if (lobby->id == id)
			{
				return lobby;
			}
		}
		return NULL;
	}

	uint32 newLobbyId()
	{
		uint32 lobbyId = 1;
		for (uint32 i = 0; i < lobbyList.size(); i++)
		{
			if (lobbyList.at(i)->id == lobbyId)
			{
				lobbyId++;
				i = 0;
			}
		}
		return lobbyId;
	}

	int32 lobby_timer(uint32 tick, CTaskMgr::CTask* PTask)
	{
		for (uint32 i = 0; i < lobbyList.size(); i++)
		{
			CLobby* lobby = lobbyList.at(i);
			if (lobby->getStatus() == LOBBY_STARTING)
			{
				uint8 tick = lobby->nextTick();
				if (tick == 0)
				{
					CGame* game = games::createGame(lobby->getMapID(), lobby->playerList);
					for (auto player : lobby->playerList)
					{
						game->addPlayer(player);
						player->pushPacket(new CGameLoadPacket(lobby->getMapID()));
					}
					lobbyList.erase(lobbyList.begin() + i);
					delete lobby;
				}
				else
				{
					for (auto player : lobby->playerList)
					{
						player->pushPacket(new CLobbyCountdownPacket(tick));
					}
				}
			}
		}
		return 0;
	}
}