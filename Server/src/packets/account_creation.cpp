

#include "account_creation.h"
#include "../lib/socket.h"

CAccountCreatePacket::CAccountCreatePacket(ACCTCREATERESPONSE response)
{
	this->type = 0x02;
	this->size = 0x03;

	WBUFB(packet, 0x02) = response;
}