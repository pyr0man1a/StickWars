

#ifndef _LOGINPACKET_H
#define _LOGINPACKET_H

#include "packet.h"

enum LOGINRESPONSE : int
{
	LOGIN_SUCCESS		=0x01,
	LOGIN_INVALID_CRED	=0x02,
	LOGIN_MAX_CAPACITY	=0x03,
	LOGIN_UNDEF			=0x04
};

class CPlayer;

class CLoginPacket : public CPacket
{
public:
	CLoginPacket(CPlayer*, LOGINRESPONSE response);
};


#endif