
#include "player_update.h"
#include "../player.h"

#include "../lib/socket.h"

CPlayerUpdatePacket::CPlayerUpdatePacket(CPlayer* player)
{
	this->type = 0x14;
	this->size = 0x0A;

	WBUFL(packet, 0x02) = player->GetMoney();
	WBUFL(packet, 0x16) = player->GetScore();
}