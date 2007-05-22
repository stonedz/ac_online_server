/*
 * This is a simple native functions library that perform server startup
 * and socket connections.
 */
#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_thread.h"
#include "SDL_net.h"

#include "Connection.h"
#include "../Server.h"
#include "../Logger.h"
#include "amx.h"

#ifdef TESTPHASE
#include "../Account.h"
#endif


static cell AMX_NATIVE_CALL n_StartServer(AMX *amx, const cell *params)
{
	int ret = 0;

// 	// A logger, used to log server messages.
// 	Logger* logger = Logger::getInstance();
//
// 	#ifdef TESTPHASE
// 	logger->setDebugMode(true);
// 	#endif
//
// 	logger->log("Initializing SDL subsystems...", LOGMODE_NORMAL);
//
// 	/*
// 	 * Initializes SDL, this maybe should be moved to another class...
// 	 */
// 	if(SDL_Init(0)==-1)
// 	{
// 		cerr << "SDL_Init: "<< SDL_GetError() << endl;
// 		exit(1);
// 	}
//
// 	/*
// 	 * Initializes SDL_net, this maybe should be moved to another class...
// 	 */
// 	if(SDLNet_Init()==-1)
// 	{
// 		cerr << "SDLNet_Init: " << SDLNet_GetError() << endl;
// 		SDL_Quit();
// 		exit(2);
// 	}
//
// 	// What to do before exiting.
// 	atexit(SDL_Quit);
//
// 	cout << "OK" << endl << endl;
//
// 	cout << "Creating a new server instance...";
// 	Server* server = new Server(9999);
// 	cout << "OK" << endl << endl;
//
// 	SDL_WaitThread(server->getThread(), NULL);
// 	//
// 	// 	return 0;

	std::cout<<"Caffaz merda"<<std::endl;

	return ret;
}

/*
#if defined __cplusplus
extern "C"
#endif
*/
const AMX_NATIVE_INFO serverLanguages_Natives[] = {
	{ "StartServer", n_StartServer},
	{ NULL, NULL}
};

int AMXEXPORT amx_ServerLanguageInit(AMX *amx)
{
	return amx_Register(amx, serverLanguages_Natives, -1);
}

int AMXEXPORT amx_ServerLanguageCleanup(AMX *amx)
{
	return AMX_ERR_NONE;
}
