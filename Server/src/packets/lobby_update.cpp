
#include "lobby_update.h"

#include "../lib/socket.h"
#include "../player.h"
#include "../lobby.h"

CLobbyUpdatePacket::CLobbyUpdatePacket(CLobby* lobby)
{
	this->type = 0x03;
	this->size = 0x10 * lobby->playerList.size() + 4;

	WBUFB(packet, 0x02) = lobby->getMaxSize();
	WBUFB(packet, 0x03) = lobby->getMapID();
	WBUFB(packet, 0x04) = lobby->playerList.size();

	for (uint8 i = 0; i < lobby->playerList.size(); i++)
	{
		WBUFL(packet, 0x05 + i * 0x10) = lobby->playerList.at(i)->id;
		WBUFB(packet, 0x09 + i * 0x10) = lobby->playerList.at(i)->GetTeam();
		WBUFB(packet, 0x0A + i * 0x10) = lobby->playerList.at(i)->GetColor();
		memcpy(packet + 0x0B + i * 0x10, lobby->playerList.at(i)->GetName(), 10);
	}
}