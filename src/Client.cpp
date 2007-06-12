#include "Client.h"

#include "Server.h"
#include "Account.h"
#include "Clientfsm.h"

Client::Client(TCPsocket socket, Server* server)
	:myServer(server),
	myAccount(NULL)
{
	this->data->socket = socket;// This is our socket.
	this->data->running = true; // The server is running ...
	this->data->self = this;	// Pointer to the object itself (useful for threading)
	this->data->id= 0; 		// This may be set as the key of clients' map ...

	/*
	 * Creates a new thread for the server socket.
	 */
	 this->data->thread = SDL_CreateThread(startThread, this->data);
	 if (this->data->thread == NULL) {
	 	std::cerr << "SDL_CreateThread: " << SDL_GetError() << std::endl;
        exit(5);
    }
}

Client::~Client(){
    if (myAccount)
        delete myAccount;
}

void Client::startListen(ConnectionData * data){
	ClientFSM* fsm = new ClientFSM(data, myServer, this);

	fsm->Start();				// Starts a new finite states machine
	while(!(fsm->getStatus())){	// and runs it while requested.
		fsm->Evolve();
		SDL_Delay(100);
	}
	//Deletes the FSM
	delete fsm;

	// Deletes the client from Server's clients' map, if this fails
	// it means that incorrect username or password has been 
	// provided. In this case delete myself.
	if(!this->myServer->removeClient(this))
		delete this;
}

void Client::setAccount(Account* account){
    myAccount = account;
}

Server& Client::getServer(){
    return *myServer;
}

void Client::save(){
    myAccount->save();
}
