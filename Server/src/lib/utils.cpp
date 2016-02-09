/*
===========================================================================

  Copyright (c) 2010-2014 Darkstar Dev Teams

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see http://www.gnu.org/licenses/

  This file is part of DarkStar-server source code.

===========================================================================
*/

#include "utils.h"
#include "showmsg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
#	include <intrin.h>
#endif

/************************************************************************
*																		*
*																		*
*																		*
************************************************************************/

int32 intpow32(int32 base, int32 exponent)
{
	int32 power = 1;
	while (exponent)
	{
		if (exponent & 1)
			power *= base;
		exponent >>= 1;
		base *= base;
	}
	return power;
}

/************************************************************************
*																		*
*																		*
*																		*
************************************************************************/

void getMSB(uint32* result,uint32 value)
{
	*result = 0;
	if(value == 0)
		return;
#ifdef __GNUC__
	*result = 31 - (unsigned) __builtin_clz (value);
#elif defined _MSC_VER
	_BitScanReverse((unsigned long*)result,value);
#else
	while (value >>= 1)
		(*result)++;
#endif

}


/************************************************************************
*																		*
*  BitOp functions														*
*																		*
************************************************************************/

int32 hasBit(uint16 value, uint8* BitArray, uint32 size)
{
	if (value >= size * 8)
	{
		ShowError(CL_RED"hasBit: value (%u) is out of range\n" CL_RESET, value);
		return 0;
	}
	return (int32)(BitArray[value >> 3] & (1 << (value % 8)));
}

int32 addBit(uint16 value, uint8* BitArray, uint32 size)
{
	if (!hasBit(value, BitArray, size) && (value < size * 8))
	{
		BitArray[value >> 3] |= (1 << (value % 8));
		return 1;
	}
	return 0;
}

int32 delBit(uint16 value, uint8* BitArray, uint32 size)
{
	if(hasBit(value, BitArray, size))
	{
		BitArray[value >> 3] &= ~(1 << (value % 8));
		return 1;
	}
	return 0;
}

/************************************************************************
*																		*
*																		*
*																		*
************************************************************************/

uint32 packBitsBE(uint8* target, uint64 value, int32 bitOffset, uint8 lengthInBit)
{
	return packBitsBE(target, value, 0, bitOffset, lengthInBit);
}

uint32 packBitsBE(uint8* target, uint64 value, int32 byteOffset, int32 bitOffset, uint8 lengthInBit)
{
	byteOffset += (bitOffset >> 3);										//correct bitOffsets>=8
	bitOffset  %= 8;

	uint64 bitmask = 0xFFFFFFFFFFFFFFFFLL;								//Generate bitmask

	bitmask >>= (64-lengthInBit);
	bitmask <<= bitOffset;

	value <<= bitOffset;												//shift value
	value  &= bitmask;

	bitmask ^= 0xFFFFFFFFFFFFFFFFLL;									//invert bitmask

	if ((lengthInBit+bitOffset) <= 8)									//write shifted value to target
	{
		uint8* dataPointer = (uint8*)&target[byteOffset];

		uint8 bitmaskUC = (uint8)bitmask;
		uint8 valueUC   = (uint8)value;

		*dataPointer &= bitmaskUC;
		*dataPointer |= valueUC;
	}
	else if ((lengthInBit+bitOffset) <= 16)
	{
		uint16* dataPointer = (uint16*)&target[byteOffset];

		uint16 bitmaskUC = (uint16)bitmask;
		uint16 valueUC   = (uint16)value;

		*dataPointer &= bitmaskUC;
		*dataPointer |= valueUC;
	}
	else if ((lengthInBit+bitOffset) <= 32)
	{
		uint32* dataPointer = (uint32*)&target[byteOffset];

		uint32 bitmaskUC = (uint32)bitmask;
		uint32 valueUC   = (uint32)value;

		*dataPointer &= bitmaskUC;
		*dataPointer |= valueUC;
	}
	else if ((lengthInBit+bitOffset) <= 64)
	{
		uint64* dataPointer = (uint64*)&target[byteOffset];

		*dataPointer &= bitmask;
		*dataPointer |= value;
	}
	else
	{
		ShowError("Pack Bits Error: packBitsBE(...) not implemented for targetsizes above 64 bits.\n Targetsize: %d\n",(lengthInBit+bitOffset));
	}
	return ((byteOffset << 3) + bitOffset + lengthInBit);
}


uint64 unpackBitsBE(uint8* target, int32 bitOffset, uint8 lengthInBit)
{
	return unpackBitsBE(target, 0, bitOffset, lengthInBit);
}

uint64 unpackBitsBE(uint8* target, int32 byteOffset, int32 bitOffset, uint8 lengthInBit)
{
	byteOffset += (bitOffset >> 3);
	bitOffset  %= 8;

	uint64 bitmask = 0xFFFFFFFFFFFFFFFFLL;

	bitmask >>= (64-lengthInBit);
	bitmask <<= bitOffset;

	uint64 retVal;

	if ((lengthInBit+bitOffset) <= 8)
	{
		uint8* dataPointer=(uint8*)&target[byteOffset];

		retVal = ((*dataPointer)&(uint8)bitmask) >> bitOffset;
	}
	else if ((lengthInBit+bitOffset) <= 16)
	{
		uint16* dataPointer = (uint16*)&target[byteOffset];

		retVal = ((*dataPointer)&(uint16)bitmask) >> bitOffset;
	}
	else if ((lengthInBit+bitOffset) <= 32)
	{
		uint32* dataPointer = (uint32*)&target[byteOffset];

		retVal = ((*dataPointer)&(uint32)bitmask) >> bitOffset;
	}
	else if ((lengthInBit+bitOffset) <= 64)
	{
		uint64* dataPointer = (uint64*)&target[byteOffset];

		retVal = ((*dataPointer)&(uint64)bitmask) >> bitOffset;
	}
	else
	{
		ShowError("Unpack Bits Error: unpackBits(...) not implemented for targetsizes above 64 bits.\n Targetsize: %d\n",(lengthInBit+bitOffset));
		return 0;
	}
	return retVal;
}

uint32 packBitsLE(uint8* target, uint64 value, int32 bitOffset, uint8 lengthInBit)
{
	return packBitsLE(target, value, 0, bitOffset, lengthInBit);
}

uint32 packBitsLE(uint8* target, uint64 value, int32 byteOffset, int32 bitOffset, uint8 lengthInBit)
{
	byteOffset += (bitOffset >> 3);													//correct bitOffsets >= 8
	bitOffset  %= 8;

	uint8 bytesNeeded;																//calculate how many bytes are needed
	if ((bitOffset + lengthInBit) <= 8)
		bytesNeeded = 1;
	else if ((bitOffset + lengthInBit) <= 16)
		bytesNeeded = 2;
	else if ((bitOffset + lengthInBit) <= 32)
		bytesNeeded = 4;
	else if ((bitOffset + lengthInBit) <= 64)
		bytesNeeded = 8;
	else
	{
		ShowError("Pack Bits Error: packBitsLE(...) not implemented for targetsizes above 64 bits.\n Targetsize: %d\n",(lengthInBit+bitOffset));
		return 0;
	}

	uint8* modifiedTarget = new uint8[bytesNeeded];									//convert byteOrder to Big Endian

	for (uint8 curByte = 0; curByte < bytesNeeded; ++curByte)
	{
		modifiedTarget[curByte] = target[byteOffset+(bytesNeeded-1)-curByte];
	}

	int32 newBitOffset = (bytesNeeded << 3) - (bitOffset + lengthInBit); 			//calculate new bitOffset

	packBitsBE(&modifiedTarget[0], value, 0, newBitOffset, lengthInBit);			//write data to modified array

	for (uint8 curByte = 0; curByte < bytesNeeded; ++curByte)						//copy back to target
	{
		target[byteOffset+(bytesNeeded-1)-curByte] = modifiedTarget[curByte];
	}

	if (modifiedTarget) delete[] modifiedTarget;
    return ((byteOffset << 3) + bitOffset + lengthInBit);
}

uint64 unpackBitsLE(uint8* target, int32 bitOffset, uint8 lengthInBit)
{
	return unpackBitsLE(target, 0, bitOffset, lengthInBit);
}

uint64 unpackBitsLE(uint8* target, int32 byteOffset, int32 bitOffset, uint8 lengthInBit)
{
	byteOffset += (bitOffset >> 3);
	bitOffset  %= 8;

	uint8 bytesNeeded;
	if ((bitOffset + lengthInBit) <= 8)
		bytesNeeded = 1;
	else if ((bitOffset + lengthInBit) <= 16)
		bytesNeeded = 2;
	else if ((bitOffset + lengthInBit) <= 32)
		bytesNeeded = 4;
	else if ((bitOffset + lengthInBit) <= 64)
		bytesNeeded = 8;
	else
	{
		ShowError("Unpack Bits Error: packBitsLE(...) not implemented for targetsizes above 64 bits.\n Targetsize: %d\n",(lengthInBit+bitOffset));
		return 0;
	}

	uint64 retVal;

	uint8* modifiedTarget = new uint8[bytesNeeded];

	for (uint8 curByte=0; curByte < bytesNeeded; ++curByte)
	{
		modifiedTarget[curByte]=target[byteOffset+(bytesNeeded-1)-curByte];
	}
	if (bytesNeeded == 1)
	{
		uint8 bitmask = 0xFF >> bitOffset;
		retVal = (modifiedTarget[0]&bitmask) >> (8-(lengthInBit+bitOffset));
	}
	else
	{
		int32 newBitOffset = (bytesNeeded*8)-(bitOffset+lengthInBit);
		retVal = unpackBitsBE(&modifiedTarget[0],0,newBitOffset,lengthInBit);
	}

	if (modifiedTarget) delete []modifiedTarget;
	return retVal;
}

std::string escape(std::string const &s)
{
	std::size_t n = s.length();
	std::string escaped;
	escaped.reserve(n * 2);
	for (std::size_t i=0;i<n;++i){
		if (s[i]=='\\' || s[i]=='\'')
			escaped+='\\';
		escaped +=s[i];
	}
	return escaped;
}