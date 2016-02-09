
#include "action.h"
#include "../lib/socket.h"
#include "../player.h"
#include "../Unit.h"

CActionPacket::CActionPacket(Unit* initiator, Unit* target, ACTION action, int8 dmginit, int8 dmgtarget, std::pair<uint8, uint8> pos)
{
	this->type = 0x15;
	this->size = 0x0B;

	WBUFW(packet, 0x02) = initiator->getID();
	WBUFB(packet, 0x04) = pos.first;
	WBUFB(packet, 0x05) = pos.second;
	WBUFB(packet, 0x06) = action;
	WBUFW(packet, 0x07) = target->getID();
	WBUFB(packet, 0x09) = dmginit;
	WBUFB(packet, 0x0A) = dmgtarget;
}