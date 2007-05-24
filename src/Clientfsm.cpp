#include "Clientfsm.h"

#include "Connection.h"
#include "MessageIn.h"
#include "MessageOut.h"
#include "Logger.h"
#include "Server.h"
#include "crc32.h"
#include "sha1.h"
#include "cppsqlite3.h"
#include "Account.h"
#include "Client.h"
#include "Char.h"

ClientFSM::ClientFSM(ConnectionData * data, Server* server,Client* client)
	: endFSM(false),
	data(data),
	set(SDLNet_AllocSocketSet(1)), // Allocate a new set for the client.
	lastKA(SDL_GetTicks()),
	logger(Logger::getInstance()),
	myServer(server),
	myClient(client)
{
	if(!set) {
		std::cerr << "SDLNet_AllocSocketSet: " << SDLNet_GetError() << endl;
		exit(0);
	}
	SDLNet_TCP_AddSocket(this->set, this->data->socket); // Add our TCP socket to the set.
	std::cerr <<"Client thread socket id: "<< data->socket << std::endl;
}

void ClientFSM::Start(){
	ExecState = &ClientFSM::Login;
}

void ClientFSM::Evolve(){
	(this->*ExecState)();
}

void ClientFSM::Stop(){
}

bool ClientFSM::ExecTrans(client_fsm_trans t){
	switch (t)
	{
	case t_login_ok:
		ExecState = &ClientFSM::Ready;
		break;
	case t_ka_received:
		ExecState = &ClientFSM::ResetKATime;
		break;
	case t_ack_time:
		ExecState = &ClientFSM::SendKA_ACK;
		break;
	case t_ka_ack_sent:
		ExecState = &ClientFSM::Ready;
		break;
	case t_ka_timeout:
		ExecState = &ClientFSM::Disconnect;
		break;
	case t_disconnect:
		ExecState = &ClientFSM::Disconnect;
		break;
	default:
		std::cerr << "Unsupported transition in ClientFSM" << std::endl;
	}

return true;
}



void ClientFSM::Login(){
	Sint32 ready = 0;
	MessageIn* message = NULL;

	ready = SDLNet_CheckSockets(this->set, 10000);// Check for socket's activity
	if(ready==-1){ // An error occurred, disconnect the socket.
		std::cerr << "SDLNet_CheckSockets: " << SDLNet_GetError() << endl;
		ExecTrans(t_disconnect);
	}
	if(SDLNet_SocketReady(data->socket)){
		message = Connection::getMessage(data->socket);
		if (message->getType() == MSG_LOGIN) // We now proceed with the autentication process
		{
			bool authenticated = false;
			authenticated = authenticate(message);
			if (authenticated == true)
			{
				ExecTrans(t_login_ok);
			}
			else
			{
				ExecTrans(t_disconnect);
			}
		}
		else
		{
			ExecTrans(t_disconnect);
		}
		delete message;
	}
	else
	{
		ExecTrans(t_disconnect); // No data to read means no username and pasword, something went wrong.
	}
}

void ClientFSM::SendKA_ACK(){
	MessageOut* messageout;
	messageout = new MessageOut(MSG_KA_ACK);

	messageout->write2(0);
	messageout->addCRC();
	Connection::putMessage(data->socket, messageout);

	delete messageout;

	ExecTrans(t_ka_ack_sent);
}

void ClientFSM::Ready(){

	if ((SDL_GetTicks() - lastKA) > KEEPALIVE_TIMEOUT){
		std::cerr<<"KEEPALIVE_TIMEOUT occoured\n";
		ExecTrans(t_ka_timeout);
	}
	else{
		Sint32 ready = 0;
		MessageIn* messagein = NULL;

		ready = SDLNet_CheckSockets(this->set,0); // Check for socket's activity.
		if(ready==-1){
			std::cerr << "SDLNet_CheckSockets: " << SDLNet_GetError() << std::endl; // An error occurred, disconnect the socket.
			ExecTrans(t_disconnect);
		}
		if(SDLNet_SocketReady(data->socket)){
			messagein = Connection::getMessage(data->socket);
                if (messagein){
                    if (messagein->getType() == MSG_KA){
                        ExecTrans(t_ka_received);
                    }
                    else if (messagein->getType() == MSG_CHAT){ // General chat message received.
                        chat(messagein);
                    }
                    else if (messagein->getType() == MSG_MOVE){ // A movement message received.
                        move(messagein);
                    }
                }
                else{
                    logger->log("Error crating a valid MessageIn in ClientFSM ready loop! <Additional client info here>", LOGMODE_ERROR);
                }
			delete messagein;
		}
	}
}

void ClientFSM::Disconnect(){
	std::cout << "Closing connection with Client " << this->data->socket << "...";
	SDLNet_FreeSocketSet(this->set);
	this->set = NULL;
	SDLNet_TCP_Close(this->data->socket);
	this->data->socket = NULL;
	this->data->running = false;
	this->endFSM = true;
	std::cout << "OK"<< std::endl;
}

void ClientFSM::ResetKATime(){
	lastKA = SDL_GetTicks();
	ExecTrans(t_ack_time);
	//std::cerr<<"ResetKATime\n";
}

bool ClientFSM::authenticate(MessageIn *msg){
	bool ret = false;
	CppSQLite3DB db;

	string login_data = msg->readString();
	std::cout << "Received a login request, processing it..." << std::endl;

	if (msg->checkCRC()){
        try{
            db.open("accounts.db");
            string tmpQuery = "SELECT * FROM registered_users WHERE index_hash = '"+login_data+"';";

            CppSQLite3Query q = db.execQuery(tmpQuery.data());
            if (!q.eof()){ // found a valid hash.
                this->myClient->setAccount(new Account(myServer, myClient, q.getIntField(0),q.fieldValue(1),q.fieldValue(3),q.fieldValue(4),q.fieldValue(5),q.getIntField(6))); // Attach an account to the Client.
                ret = true;
            }

            db.close();
	    }
	    catch(CppSQLite3Exception& e){
	        logger->log("Authentication failed due to a database problem.", LOGMODE_AUTH);
            logger->log(e.errorMessage(), LOGMODE_DB);
	    }

	}
	else{
	    string toLog = "!! Failed CRC check during authentification ";
		logger->log(toLog, LOGMODE_AUTH);
	}

	return ret;
}

void ClientFSM::chat(MessageIn* message){
    Uint32 tmp = reinterpret_cast<Uint32>(this->data->self); // Client* to an int in order to find the client in mClients map.
    // A MSG_CHAT has been received
    myServer->generalChatMsg(tmp, message->readString());

}

void ClientFSM::move(MessageIn* message){
    Uint16 len, x, y ,z;
    len = message->read2();
    if (len == 6){
        x = message->read2();
        y = message->read2();
        z = message->read2();
        #ifdef TESTPHASE
        std::cout << "Received a Move message, new coord are x:" << x << " y:" << y << std::endl;
        #endif

        const Location* actualLocation = myClient->getAccount()->getChar()->getPosition();
        const Location* destLocation = new Location(x,y,z);
        //myServer->getMapManager()->validateMove(ORIG,DEST); <- TODO to be implemented!
        myClient->getAccount()->getChar()->setDestination(*destLocation);
    }
    else
        logger->log("Bad lenght in MSG_MOVE message <additional info here>", LOGMODE_ERROR); //TODO : fill additional info
}

bool ClientFSM::getStatus(){
	return this->endFSM;
}
