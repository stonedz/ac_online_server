#include "Connection.h"

#include "Message.h"
#include "MessageIn.h"
#include "MessageOut.h"
#include "NetPacket.h"
#include "crc32.h"
#include "Logger.h"

Connection::Connection()
	:data(new ConnectionData())
{
}

Connection::~Connection()
{
	delete this->data;
}

int Connection::startThread(void * data){
	ConnectionData* trueData = reinterpret_cast<ConnectionData *>(data);
	trueData->self->startListen(trueData); // Calls the correct object's method.
	return 1;
}


SDL_Thread* Connection::getThread(){
	return this->data->thread;
}

TCPsocket Connection::getSocket(){
    return this->data->socket;
}

MessageIn* Connection::getMessage(TCPsocket socket){
	Uint32 result;
	message_type type;
	Uint16 len;
	Uint32 crc;
	char* msg;
	char* buf;
    Logger* logger = Logger::getInstance();

	result=SDLNet_TCP_Recv(socket,(char *) &type,2); // Gets message's type
	if(result<2) {
		if(SDLNet_GetError() && strlen(SDLNet_GetError())) // sometimes blank!
			printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
        logger->log("No message type in TCP socket.", LOGMODE_NORMAL);
		return NULL;
	}

	result=SDLNet_TCP_Recv(socket,(char *) &len,2);// Gets payload's size
	if(result<2) {
		if(SDLNet_GetError() && strlen(SDLNet_GetError())) // sometimes blank!
			printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
			logger->log("No message lenght in TCP socket.", LOGMODE_NORMAL);
		return NULL;
	}

	msg = (char*) malloc (SDL_SwapBE16(len)); // Gets the payload

	result=SDLNet_TCP_Recv(socket,msg,SDL_SwapBE16(len));
	if(result<(SDL_SwapBE16(len))) {
		if(SDLNet_GetError() && strlen(SDLNet_GetError())) // sometimes blank!
			printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
		free(msg);
		logger->log("No message payload in TCP socket.", LOGMODE_NORMAL);
		return NULL;
	}

	result=SDLNet_TCP_Recv(socket,(char *) &crc, 4); // Gets the CRC
	if(result < 4){
		if(SDLNet_GetError() && strlen(SDLNet_GetError())) // sometimes blank!
			printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
        logger->log("No message CRC in TCP socket.", LOGMODE_NORMAL);
		return NULL;
	}

	buf = (char*) malloc (SDL_SwapBE16(len) + 8); 	// 8 = (type)+(payload size)+(crc)

	memcpy(buf, (char *) &type , 2);
	memcpy(buf + 2, (char *) &len, 2);
	memcpy(buf + 4, (char *) msg, SDL_SwapBE16(len));
	memcpy((buf + 4 + SDL_SwapBE16(len)),(char *) &crc ,4);

	free(msg);

	NetPacket* packet = new NetPacket(buf, (SDL_SwapBE16(len) + 8));// This will be destroyed by MessageIn destructor.
	MessageIn* message = new MessageIn(packet);

	free(buf);

	return message;
}

Uint32 Connection::putMessage(TCPsocket socket, MessageOut* msg){
	Uint32 result;
	const NetPacket* packet = msg->getPacket();
	char *tmp = packet->data;

	result=SDLNet_TCP_Send(socket,tmp,(packet->len));
	if(result<(packet->len)) {
		if(SDLNet_GetError() && strlen(SDLNet_GetError())) // sometimes blank!
			printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		return(0);
	}

	return result;
}
