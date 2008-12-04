#include "Cmd_login.h"
#include "../network/Connection.h"
#include "../network/Message.h"
#include "../network/MessageIn.h"
#include "../network/MessageOut.h"
#include "../network/crc32.h"
#include "../network/sha1.h"


Cmd_login::~Cmd_login()
{
    //dtor
}

void Cmd_login::help(){
    std::cout << "Tests the server by performing a login." << std::endl;
}

void Cmd_login::execute(){
    IPaddress ipAddress;
	TCPsocket sck;
	SDLNet_SocketSet sckSet;

	SDLNet_ResolveHost(&ipAddress, "127.0.0.1" , 9999);
	sck = SDLNet_TCP_Open(&ipAddress);
	if (sck)
	{
		int numUsed;
		sckSet = SDLNet_AllocSocketSet(1);
		// @todo Add AddSocket return value handling
		numUsed = SDLNet_TCP_AddSocket(sckSet, sck);

		std::string tmpData = "PioloPiolo";
        CRC32 loginCRC;
        SHA1 shaLogin;
        unsigned short strLen;
        strLen = (unsigned short) tmpData.size();
        unsigned int shaData[5];
        shaLogin.Reset();
        // @todo: make this passage cleaner. :D
        const char *c;
        c = tmpData.c_str();
        for (int i = 0; i < strLen; i++)
        {
            shaLogin.Input(c[i]);
        }
        if (!shaLogin.Result(shaData))
        {
            //tmpStr += "Sha could not compute message digest for login informations.\n";
            return;
        }

        //tmpStr += "SHA-1: ";
        char s[512];
        for (int i = 0; i < 5; i++)
        {
            sprintf(s, "0x%8x ", shaData[i]);
        }
        //tmpStr += (CEGUI::String) s + "\n";

        //std::cout << "SHA-1: " << tmpStr;

        char hash[40];
        for (int i = 1; i < 6; i++)
        {
		// Transforms the hash in a readable format.
            sprintf(hash + (8 * (i - 1)), "%08x", shaData[i-1]);
        }
        MessageOut* messageout;
        messageout = new MessageOut(MSG_LOGIN);

        messageout->writeString(hash);
        std::cout << messageout->addCRC();
        Connection::putMessage(sck, messageout);

        delete messageout;

        for (int counter=0; counter < 10; counter ++){
            MessageOut* messageout;
            messageout = new MessageOut(MSG_KA);

            messageout->write2(0);
            messageout->addCRC();
            Connection::putMessage(sck, messageout);

            delete messageout;
            SDL_Delay(1000);
        }

    }

}


