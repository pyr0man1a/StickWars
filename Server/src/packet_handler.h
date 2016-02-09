

#ifndef _PACKETHANDLER_H
#define _PACKETHANDLER_H

#include "lib/cbasetypes.h"

class CPlayer;
struct session_data_t;

namespace packethandler
{
	extern uint8 PacketSizes[256];
	extern void(*PacketParser[256])(session_data_t*, CPlayer*, int8*);

	void init();
}

#endif