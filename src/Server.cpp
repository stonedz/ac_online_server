#include "Server.h"
#include "MessageOut.h"
#include "Message.h"
#include "Client.h"
#include "Gamefsm.h"
#include "MapManager.h"

#include <sstream>

Server::Server(int port)
	:mxClients(SDL_CreateMutex()),
	myMapManager(MapManager::getInstance()),
	exit_request(false),
	chat_mode(false),
	mxGoSerial(SDL_CreateMutex()),
	myIdServer(new IDServer(this)),
	initialized(false),
	myGamefsm(this),
	myConsole(this)
{
	/*
	 * Fills the IPaddress object with correct data to create
	 * a valid TCP listening socket for the server.
	 */
	if(SDLNet_ResolveHost(&(this->data->address),NULL,port)==-1)
	{
		std::cerr << "SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
		SDLNet_Quit();
		SDL_Quit();
		exit(3);
	}

	/*
	 * Creates the server's socket that will accept new connections.
	 */
	this->data->socket = SDLNet_TCP_Open(&(this->data->address));
	if(!(this->data->socket)){
		std::cerr << "SDserverDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
		exit(4);
	}

	this->data->running = true; // The server is running ...
	this->data->self = this;	// Pointer to self.
	this->data->id= 0;			// For the moment we set this to 0.

	/*
	 * Creates a new thread for the server socket.
	 */
	 this->data->thread = SDL_CreateThread(startThread, this->data);
	 if (this->data->thread == NULL) {
	 	std::cerr << "SDL_CreateThread: " << SDL_GetError() << std::endl;
        exit(5);
    }
}

Server::~Server(){
	SDL_DestroyMutex(mxClients);
	SDL_DestroyMutex(mxGoSerial);
	delete myIdServer;
}

void Server::startListen(ConnectionData * data){
	int ready = 0;
	TCPsocket newSocket = NULL;
	SDLNet_SocketSet set = NULL;
	Client* newClient = NULL;

	set = SDLNet_AllocSocketSet(1);
	if(!set) {
		std::cerr << "SDLNet_AllocSocketSet: " << SDLNet_GetError() << std::endl;
		exit(0);
	}
	SDLNet_TCP_AddSocket(set, data->socket);

	if(myMapManager->loadXMLMap(MAP_TESTING)){
		std::ostringstream tmp;
		tmp << "Loaded XML Map -> " << MAP_TESTING << ".xml";
		myConsole.printMsg(tmp);
	}
	else{
		std::ostringstream tmp;
		tmp << "Failed to load Map -> " << MAP_TESTING << ".xml";
		myConsole.printMsg(tmp, CONSOLE_ERROR);
		return;
	}
	
	if(myMapManager->loadBinTMap(MAP_T)){
		std::ostringstream tmp;
		tmp << "Loaded Terrain Map -> " << MAP_T;
		myConsole.printMsg(tmp);
	}
	else{
		std::ostringstream tmp;
		tmp << "Failed to load Map -> " << MAP_T;
		myConsole.printMsg(tmp, CONSOLE_ERROR);
		return;
	}	
	
	myGamefsm.Start(); // Starts the game state machine.

	while(!initialized){ // Wait for the server to be initialized
		SDL_Delay(100);
	}

	// Now the server is up and running, inform the user.
	myConsole.printMsg("Server is now running!");

	// Main server loop. Here we accept new connections.
	while(!exit_request){
		ready = SDLNet_CheckSockets(set, (Uint32) 50);
		if(ready==-1){
			std::cout << "SDLNet_CheckSockets: " << SDLNet_GetError() << std::endl;
			break;
		}
		if(!ready)
			continue;
		if(SDLNet_SocketReady(data->socket)){
			newSocket=SDLNet_TCP_Accept(data->socket);
			if (newSocket){
				newClient = new Client(newSocket, this);
				//addClient(newClient);
				#ifdef TESTPHASE
				myConsole.printMsg("Connection received, authenticating it...");
				//std::cout << std::endl << "<Server> Now " << this->mClients.size() << " clients are connected." << std::endl;
				#endif
			}
		}
	}

	SDLNet_FreeSocketSet(set);
	// Since the server is exiting do the same with the game FSM.
	myGamefsm.Stop();
	SDL_Thread* tmpThread = myGamefsm.getThread();
	if (tmpThread != NULL) // If necessary wait for the GameFSM to finish.
        SDL_WaitThread(tmpThread, NULL);

	myConsole.printMsg("Server is now quitting, good bye!");

}


bool Server::addClient(Client* newClient){
	Uint32 tmp = reinterpret_cast<Uint32>(newClient);

	SDL_LockMutex(this->mxClients); // Locks the mutex..
	this->mClients.insert(std::pair<Uint32, Client*>(tmp,newClient));// Adds the client to the map.
	SDL_UnlockMutex(this->mxClients);// ...unlocks the mutex
	return true;
	///else
	//	return false;
}

bool Server::removeClient(Client* oldClient){
	Uint32 tmp = reinterpret_cast<Uint32>(oldClient);

	SDL_LockMutex(this->mxClients);// Locks the mutex...
	std::map<Uint32, Client*>::iterator i;// Gets an iterator for the clients' map.

	i = this->mClients.find(tmp);
		if (i != this->mClients.end()){ // Client found!
		delete i->second;
		this->mClients.erase(i);
		SDL_UnlockMutex(this->mxClients);// ...unlocks the mutex
		return true;
	}
    else{ // Client is not in the map...that's bad I guess..
		SDL_UnlockMutex(this->mxClients);// ... unlocks the mutex
		return false;
	}
}

void Server::requestExit(){
    exit_request = true;
}

void Server::setChatMode(bool value){
    chat_mode = value;
}

void Server::generalChatMsg(Uint32 sender, std::string msg){
    if (chat_mode && sender != 0) // The sender 0 (zero) is the server itself!
        std::cout << msg << std::endl;

    std::map<Uint32, Client*>::iterator p;
    for (p = mClients.begin(); p != mClients.end(); p++){
        if(p->first != sender){ // don't sentd the message to the original sender.
            MessageOut* messageout = new MessageOut(MSG_CHAT);
            messageout->writeString(msg);
            messageout->addCRC();
            Connection::putMessage(p->second->getSocket(), messageout);
            delete messageout;
        }
    }
}

void Server::getNextGoSerial(Uint32& validSerial){
    SDL_LockMutex(this->mxGoSerial);
    //validSerial = gameObjectSerial++;
    SDL_UnlockMutex(this->mxGoSerial);
    return;
}

void Server::getNewID(Uint64& id, const Uint8& type){
	SDL_LockMutex(this->mxGoSerial);
	id = myIdServer->getNewId(type);
	SDL_UnlockMutex(this->mxGoSerial);
	return;
}

Uint32 Server::updateIDServer(){
	Uint32 newTimeSlice;
   	SDL_LockMutex(this->mxGoSerial);
	newTimeSlice = myIdServer->updateTime();
	SDL_UnlockMutex(this->mxGoSerial);
	return newTimeSlice;
}

void Server::setInit(bool value){
    initialized = value;
}
