
#include "game_load.h"

#include "../lib/socket.h"

CGameLoadPacket::CGameLoadPacket(uint8 mapID)
{
	this->type = 0x10;
	this->size = 0x03;

	WBUFB(packet, 0x02) = mapID;
}