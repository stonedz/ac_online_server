#include "CommandScheduler.h"
#include "cppsqlite3.h"
#include "Logger.h"

CommandScheduler* CommandScheduler::pUniqueInstance = NULL; // Reference to the unique instance.
SDL_mutex* CommandScheduler::mxInstance = SDL_CreateMutex();				// Reference to instance mutex.

CommandScheduler* CommandScheduler::getInstance(){
	SDL_LockMutex(mxInstance);	// Locks the mutex...
	if (pUniqueInstance == NULL){ // No instance, create one.
        pUniqueInstance = new CommandScheduler();
    }
    SDL_UnlockMutex(mxInstance);	// Unlocks the mutex...
    return pUniqueInstance;
}

void CommandScheduler::freeInstance(){
	SDL_LockMutex(mxInstance);	// Locks the mutex...
	if (pUniqueInstance != NULL) {
        delete pUniqueInstance;
        pUniqueInstance = NULL;
    }
 	SDL_UnlockMutex(mxInstance);	// Unlocks the mutex...
}

void CommandScheduler::setServer(Server* myServer){
	SDL_LockMutex(mxServer);
	this->myServer = myServer;		// Sets the CommandManager Server.
	SDL_UnlockMutex(mxServer);
}

void CommandScheduler::queue(ICommand* cmd){
    try{
        cmd->execute();
    }
    catch(CppSQLite3Exception& e){ // Database exception.
        delete cmd;
        std::string err = "Generic database error: ";
        err.append(e.errorMessage());
        err.append(".");
        std::cout << err << std::endl;
        Logger::getInstance()->log(err,LOGMODE_DB);
    }

	delete cmd;
}

CommandScheduler::CommandScheduler()
	:mxServer(SDL_CreateMutex())
{
}

CommandScheduler::~CommandScheduler()
{
	SDL_DestroyMutex(mxServer);
}
