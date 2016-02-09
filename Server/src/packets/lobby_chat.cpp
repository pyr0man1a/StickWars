
#include "lobby_chat.h"

#include "../lib/socket.h"
#include "../player.h"

CLobbyChatPacket::CLobbyChatPacket(CPlayer* player, const char* msg, int len)
{
	this->type = 0x04;
	uint32 msgsize = len > 30 ? 30 : len;
	this->size = 0x03 + msgsize;
	
	WBUFB(packet, 0x02) = msgsize;
	memcpy(packet + 0x03, player->GetName(), 10);
	memcpy(packet + 0x0D, msg, msgsize);
}