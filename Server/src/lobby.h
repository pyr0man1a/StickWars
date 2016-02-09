#ifndef _LOBBY_H
#define _LOBBY_H

#include "lib/cbasetypes.h"
#include "lib/taskmgr.h"
#include <vector>

enum LOBBYSTATUS : int
{
	LOBBY_IDLE,
	LOBBY_STARTING
};

class CPlayer;

class CLobby
{
private:
	uint8 m_maxSize;
	uint8 m_mapID;
	uint8 m_lastCountdown;
	CPlayer* m_Host;

	LOBBYSTATUS m_status;
public:

	uint32 id;
	std::vector<CPlayer*> playerList;

	uint8 getMaxSize();
	void setMapID(uint8);
	uint8 getMapID();
	void setHost(CPlayer*);
	CPlayer* getHost();
	void addPlayer(CPlayer*);
	void removePlayer(CPlayer*);
	bool hasPlayer(CPlayer*);
	uint8 playerNumber(CPlayer*);
	LOBBYSTATUS getStatus();
	uint8 nextTick();

	void startCountdown();
	void cancelCountdown();

	CLobby(uint32);
	~CLobby();
};

namespace lobbies
{
	std::vector<CLobby*> getLobbies();
	CLobby* createLobby();
	CLobby* getLobby(CPlayer*);
	CLobby* getLobby(uint32);
	uint32 newLobbyId();
	int32 lobby_timer(uint32 tick, CTaskMgr::CTask* PTask);
}

#endif