#include "MessageIn.h"

#include "NetPacket.h"
#include "crc32.h"

MessageIn::MessageIn(NetPacket* packet)
	:pos(0),
	myPacket(packet)
{
	this->myType = read2();	
}

MessageIn::~MessageIn(){
	if(this->myPacket)
		delete this->myPacket;
}

char MessageIn::read1(){
    char value = -1;
    if (this->myPacket)
    {
        if (pos < (this->myPacket)->len)
        {
            value = (this->myPacket)->data[pos];
            pos += 1;
        }
    }
    return value;
}

Uint16 MessageIn::read2(){	
    Uint16 value = 0;
    if (this->myPacket)
    {
        if (pos + 2 <= (this->myPacket)->len)
        {
            Uint16 tmp;
            memcpy(&tmp, (this->myPacket)->data + pos, 2);
            value = SDL_SwapBE16(tmp);
            pos += 2;
        }
    }
    return value;
}

Uint32 MessageIn::read4(){	
    Uint32 value = 0;
    if (this->myPacket)
    {
        if (pos + 4 <= (this->myPacket)->len)
        {
            Uint32 tmp;
            memcpy(&tmp, (this->myPacket)->data + pos, 4);
            value = SDL_SwapBE32(tmp);
            pos += 4;
        }
    }
    return value;
}

Uint32 MessageIn::getCRC(){
	 Uint32 value = 0;
	 if (this->myPacket)
    {
    	    Uint32 tmp;
            memcpy(&tmp, (this->myPacket)->data + pos, 4);
            value = SDL_SwapBE32(tmp);
            pos += 4;
    }
    return value;		
}

bool MessageIn::checkCRC()
{
	bool ret = false;
	char *tmpBuf;
	CRC32 CRC;
	Uint32 localCRC;
	Uint32 pckCRC;
	
	tmpBuf = new char [((this->myPacket)->len - 4)];
	memcpy((char *) tmpBuf, (this->myPacket)->data, ((this->myPacket)->len - 4));
	
	CRC.Init();
	localCRC = CRC.GetCRC(tmpBuf, ((this->myPacket)->len - 4));
	pckCRC = this->getCRC();
	
	if (localCRC == pckCRC)
	{
		ret = true;
	}
	
	delete [] tmpBuf;
	
	return ret;
}

std::string MessageIn::readString(Sint16 len)
{
    if (this->myPacket)
    {
        if (len < 0) { // Get string length
            len = read2();
        }
        if (len < 0 || this->pos + len > this->myPacket->len) { // Make sure the string isn't erroneous
            this->pos = (this->myPacket->len) + 1;
            return "";
        }

        // Read the string
        char const *stringBeg = (this->myPacket->data) + (this->pos);
        char const *stringEnd = (char const *)memchr(stringBeg, '\0', len);
        std::string finalString(stringBeg, stringEnd ? stringEnd - stringBeg : len);
        this->pos += len;
        return finalString;
    }
    return "";
}

void MessageIn::reset(){
	this->myType = MSG_INVALID;	
	this->pos = 0;
	if(this->myPacket)
		delete this->myPacket;
}
