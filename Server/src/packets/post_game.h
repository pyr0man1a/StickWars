

#ifndef _POSTGAMEPACKET_H
#define _POSTGAMEPACKET_H

#include "packet.h"

class CPlayer;
class CGame;

class CPostGamePacket : public CPacket
{
public:
	CPostGamePacket(CPlayer*, CGame*);
};


#endif