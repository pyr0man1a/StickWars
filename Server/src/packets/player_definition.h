

#ifndef _PLAYERDEFPACKET_H
#define _PLAYERDEFPACKET_H

#include "packet.h"

class CPlayer;

class CPlayerDefinitionPacket : public CPacket
{
public:
	CPlayerDefinitionPacket(CPlayer*, uint8);
};


#endif