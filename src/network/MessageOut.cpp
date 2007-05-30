#include "MessageOut.h"

#include "NetPacket.h"

MessageOut::MessageOut(const message_type m_type)
	:myData(NULL),
	myDataSize(0),
	pos(0),
	myPacket(NULL)
{
	write2(m_type);	//Writes the message type in the first two bytes of the message.
}

MessageOut::~MessageOut(){
	if(this->myPacket)
		delete this->myPacket;
    free(myData);
}


void MessageOut::write1(char value){
    expandData((this->pos) + 1);
    myData[this->pos] = value;
    this->pos += 1;
}

void MessageOut::write2(Uint16 value){
	expandData((this->pos) + 2);
	Uint16 tmp = SDL_SwapBE16(value);
	memcpy((this->myData)+(this->pos), &tmp, 2);
    this->pos += 2;
}

void MessageOut::write4(Uint32 value){
	expandData((this->pos) + 4);
	Uint32 tmp = SDL_SwapBE32(value);
	memcpy((this->myData)+(this->pos), &tmp, 4);
    this->pos += 4;
}

char* MessageOut::getData(){
	return this->myData;
}

Uint32 MessageOut::getDataSize(){
	return this->myDataSize;
}

const NetPacket* MessageOut::getPacket(){
	if (!this->myPacket){
        this->myPacket = new NetPacket(this->myData, this->myDataSize);
    }
    return this->myPacket;
}

void MessageOut::writeString(const string &string, Sint16 length){
    Uint16 stringLength = string.length();
    if (length < 0)
    {
        // Write the length at the start if not fixed.
        write2(stringLength);
        length = stringLength;
    }
    else if (length < stringLength)
    {
        stringLength = length; // Make sure the length of the string is no longer than specified
    }
    expandData((this->pos) + length);
    memcpy((this->myData) + (this->pos), string.c_str(), stringLength); // Write the actual string.

    if (length > stringLength) // Pad remaining space with zeros.
    {
        memset((this->myData) + (this->pos) + stringLength, '\0', length - stringLength);
    }
    this->pos += length;
}

Uint32 MessageOut::addCRC(){
	CRC32 msgCRC;
	Uint32 crc;

	msgCRC.Init();
	crc = msgCRC.GetCRC(this->myData, (this->pos));

	write4(crc);

	return crc;
}
void MessageOut::expandData(Uint16 size){

	this->myData = (char*)realloc(this->myData, size);
	this->myDataSize = size;
}
