#include "NetPacket.h"
#include <cstring>

NetPacket::NetPacket(const char *data, Uint32 size)
	:data(new char[size]),
	len(size)
{
    memcpy(this->data, data, size);
}

NetPacket::~NetPacket(){
	delete[] data;
}

char* NetPacket::getData(){	
	return this->data;
}

