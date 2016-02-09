

#ifndef _ACCOUNTCREATIONPACKET_H
#define _ACCOUNTCREATIONPACKET_H

#include "packet.h"

enum ACCTCREATERESPONSE : int
{
	CREATE_SUCCESS		=0x01,
	CREATE_NAME_INVALID	=0x02,
	CREATE_PASS_INVALID	=0x03,
	CREATE_NAME_TAKEN	=0x04,
	CREATE_UNDEF		=0x05
};

class CAccountCreatePacket : public CPacket
{
public:
	CAccountCreatePacket(ACCTCREATERESPONSE response);
};


#endif