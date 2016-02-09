

#include "packet.h"

CPacket::CPacket()
{
	this->type = 0;
	this->size = 0;

	memset(data, 0, sizeof(data));
}

uint8 CPacket::getSize()
{
	return this->size;
}

uint8 CPacket::getType()
{
	return this->type;
}