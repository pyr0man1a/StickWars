

#ifndef _LOBBYUPDATEPACKET_H
#define _LOBBYUPDATEPACKET_H

#include "packet.h"

class CLobby;

class CLobbyUpdatePacket : public CPacket
{
public:
	CLobbyUpdatePacket(CLobby*);
};


#endif