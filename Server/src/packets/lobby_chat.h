

#ifndef _LOBBYCHATPACKET_H
#define _LOBBYCHATPACKET_H

#include "packet.h"

class CPlayer;

class CLobbyChatPacket : public CPacket
{
public:
	CLobbyChatPacket(CPlayer*, const char*, int);
};


#endif