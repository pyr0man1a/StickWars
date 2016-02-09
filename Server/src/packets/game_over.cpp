
#include "game_over.h"
#include "../game.h"
#include "../player.h"

#include "../lib/socket.h"

CGameOverPacket::CGameOverPacket(CPlayer* player, uint8 playerNumber)
{
	this->type = 0x17;
	this->size = 0x07;

	WBUFB(packet, 0x02) = playerNumber;
	WBUFL(packet, 0x03) = player->id;
}