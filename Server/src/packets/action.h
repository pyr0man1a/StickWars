

#ifndef _ACTIONPACKET_H
#define _ACTIONPACKET_H

#include "packet.h"
#include <utility>

enum ACTION
{
	ACTION_MOVE,
	ACTION_ATTACK,
	ACTION_CAPTURE,
	ACTION_PRODUCE
};

class Unit;

class CActionPacket : public CPacket
{
public:
	CActionPacket(Unit* initiator, Unit* target, ACTION, int8 dmginit, int8 dmgtarget, std::pair<uint8, uint8> pos);
};


#endif