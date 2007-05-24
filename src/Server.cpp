#include "Server.h"
#include "MessageOut.h"
#include "Message.h"
#include "Client.h"
#include "Gamefsm.h"
#include "MapManager.h"

Server::Server(int port)
	:mxClients(SDL_CreateMutex()),
	exit_request(false),
	chat_mode(false),
	mxGoSerial(SDL_CreateMutex()),
	gameObjectSerial(1),
	initialized(false)
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

    Gamefsm* myGamefsm = new Gamefsm(this);
    myGamefsm->Start(); // Starts the game state machine.

    while(!initialized){ // Wait for the server to be initialized
        SDL_Delay(100);
    }

    #ifdef TESTPHASE
	std::cout << "Server " << (Uint32)(data->thread) << " is now listening." << std::endl;
	#endif

	while(!exit_request){ // Main server loop
		ready = SDLNet_CheckSockets(set, (Uint32) 500);
		if(ready==-1){
			std::cout << "SDLNet_CheckSockets: " << SDLNet_GetError() << std::endl;
			break;
		}
		if(!ready)
			continue;
		if(SDLNet_SocketReady(data->socket)){
			newSocket=SDLNet_TCP_Accept(data->socket);
			if (newSocket){
			    #ifdef TESTPHASE
				std::cout <<"Socket id: "<< newSocket << std::endl;
				#endif
				newClient = new Client(newSocket, this);
				addClient(newClient);
				#ifdef TESTPHASE
				std::cout << std::endl << "<Server> Now " << this->mClients.size() << " clients are connected." << std::endl;
				#endif
			}
		}
	}

	// Since the server is exiting do the same with the game FSM.
	myGamefsm->Stop();
	SDL_Thread* tmpThread = myGamefsm->getThread();
	if (tmpThread != NULL) // If necessary wait for the GameFSM to finish.
        SDL_WaitThread(tmpThread, NULL);

	#ifdef TESTPHASE
	std::cout << "<Server> Now quitting!" << std::endl;
	#endif
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
    validSerial = gameObjectSerial++;
    SDL_UnlockMutex(this->mxGoSerial);
    return;
}

void Server::setInit(bool value){
    initialized = value;
}
