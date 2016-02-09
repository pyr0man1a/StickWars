

#ifndef _PLAYERUPDATEPACKET_H
#define _PLAYERUPDATEPACKET_H

#include "packet.h"

class CPlayer;

class CPlayerUpdatePacket : public CPacket
{
public:
	CPlayerUpdatePacket(CPlayer*);
};


#endif