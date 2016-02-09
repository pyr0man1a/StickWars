
#include "player_defeated.h"
#include "../lobby.h"
#include "../player.h"

#include "../lib/socket.h"

CPlayerDefeatedPacket::CPlayerDefeatedPacket(CPlayer* player, uint8 playerNumber)
{
	this->type = 0x16;
	this->size = 0x07;

	WBUFB(packet, 0x02) = playerNumber;
	WBUFL(packet, 0x03) = player->id;
}