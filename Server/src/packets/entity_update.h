

#ifndef _ENTITYUPDATEPACKET_H
#define _ENTITYUPDATEPACKET_H

#include "packet.h"
#include <utility>

class Unit;

class CEntityUpdatePacket : public CPacket
{
public:
	CEntityUpdatePacket(Unit*, std::pair<uint8, uint8>);
};


#endif