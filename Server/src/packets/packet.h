

#ifndef _PACKET_H
#define _PACKET_H

#include "../lib/cbasetypes.h"

#include <string.h>

class CPacket
{
protected:
	union{
		struct {
			uint8 type;
			uint8 size;
			uint8 data[254];
		};
		uint8 packet[256];
	};

public:
	uint8 getSize();
	uint8 getType();

	CPacket();
};

#endif
