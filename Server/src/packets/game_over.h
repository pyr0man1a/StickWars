

#ifndef _GAMEOVERPACKET_H
#define _GAMEOVERPACKET_H

#include "packet.h"

class CPlayer;

class CGameOverPacket : public CPacket
{
public:
	CGameOverPacket(CPlayer*, uint8);
};


#endif