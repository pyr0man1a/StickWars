
#include "turn_change.h"

#include "../lib/socket.h"

CTurnChangePacket::CTurnChangePacket(uint8 playernumber)
{
	this->type = 0x13;
	this->size = 0x03;

	WBUFB(packet, 0x02) = playernumber;
}