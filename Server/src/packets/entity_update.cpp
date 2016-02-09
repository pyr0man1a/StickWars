
#include "entity_update.h"

#include "../lib/socket.h"
#include "../Unit.h"
#include "../player.h"
#include "../game.h"

CEntityUpdatePacket::CEntityUpdatePacket(Unit* unit, std::pair<uint8, uint8> pos)
{
	this->type = 0x11;
	this->size = 0x0A;

	WBUFW(packet, 0x02) = unit->getID();
	WBUFB(packet, 0x04) = unit->getUnitType();
	WBUFB(packet, 0x05) = unit->getOwner()->GetColor();
	WBUFB(packet, 0x06) = games::getGame(unit->getOwner())->getPlayerNumber(unit->getOwner());
	WBUFB(packet, 0x07) = pos.first;
	WBUFB(packet, 0x08) = pos.second;
	WBUFB(packet, 0x09) = unit->getHealth();
}