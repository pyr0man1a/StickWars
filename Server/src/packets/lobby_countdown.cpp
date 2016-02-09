
#include "lobby_countdown.h"

#include "../lib/socket.h"

CLobbyCountdownPacket::CLobbyCountdownPacket(uint8 time)
{
	this->type = 0x05;
	this->size = 0x03;

	WBUFB(packet, 0x02) = time;
}