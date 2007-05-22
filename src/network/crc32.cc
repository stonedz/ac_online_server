#include "crc32.h"

CRC32::CRC32()
{
}

void CRC32::Init(unsigned long pol)
{
	if (pol == 0x00000000)
	{
		// This is the official polynomial used by CRC-32
		// in PKZip, WinZip and Ethernet.
		pol = 0x04c11db7;
	}
    for(int i = 0; i <= 0xFF; i++)
	{
		crc32Table[i] = Reflect(i, 8) << 24;
		for (int j = 0; j < 8; j++)
		{
			crc32Table[i] = (crc32Table[i] << 1) ^ (crc32Table[i] & (1 << 31) ? pol : 0);
		}
		crc32Table[i] = Reflect(crc32Table[i], 32);
	} 
	
}

unsigned long CRC32::Reflect(unsigned long r, char c)
{
	unsigned long value(0);

	// Swap bit 0 for bit 7
	// bit 1 for bit 6, etc.
	for(int i = 1; i < (c + 1); i++)
	{
		if(r & 1)
		{
			value |= 1 << (c - i);
		}
		r >>= 1;
	}
	return value; 
}

unsigned long CRC32::GetCRC(char *rawData, int len)
{
	// Once the lookup table has been filled in by the two functions above,
	// this function creates all CRCs using only the lookup table.
	
	// Be sure to use unsigned variables,
	// because negative values introduce high bits
	// where zero bits are required.
	
	// Start out with all bits set high.
	unsigned long  CRC(0xffffffff);
	unsigned char *buffer;

	buffer = (unsigned char *)rawData;
	// Perform the algorithm on each character
	// in the string, using the lookup table values.
	while (len--)
	{
		CRC = (CRC >> 8) ^ crc32Table[(CRC & 0xFF) ^ *buffer++];
	}
	
	// Exclusive OR the result with the beginning value.
	return (CRC ^ 0xffffffff);
}

