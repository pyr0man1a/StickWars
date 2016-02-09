

#include "login.h"
#include "../lib/socket.h"
#include "../player.h"

CLoginPacket::CLoginPacket(CPlayer* player, LOGINRESPONSE response)
{
	this->type = 0x01;
	this->size = 0x0B;

	WBUFB(packet, 0x02) = response;
	WBUFL(packet, 0x03) = player->GetWins();
	WBUFL(packet, 0x07) = player->GetLosses();
}