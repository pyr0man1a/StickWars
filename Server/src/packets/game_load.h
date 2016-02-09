

#ifndef _GAMELOADPACKET_H
#define _GAMELOADPACKET_H

#include "packet.h"

class CPlayer;

class CGameLoadPacket : public CPacket
{
public:
	CGameLoadPacket(uint8);
};


#endif