#include <string>
#include "CommandManager.h"
#include "Logger.h"
#include "cppsqlite3.h"

#include "CommandScheduler.h"
#include "commands/Cmd_test.h"
#include "commands/Cmd_exit.h"
#include "commands/Cmd_chat.h"
#include "commands/Cmd_accounts.h"

CommandManager* CommandManager::pUniqueInstance = NULL; 	// Reference to the unique instance.
SDL_mutex* CommandManager::mxInstance = SDL_CreateMutex();	// Reference to instance mutex.

CommandManager* CommandManager::getInstance(){
	SDL_LockMutex(mxInstance);	// Locks the mutex...
	if (pUniqueInstance == NULL){ // No instance, create one.
        pUniqueInstance = new CommandManager();
    }
    SDL_UnlockMutex(mxInstance);	// Unlocks the mutex...
    return pUniqueInstance;
}

void CommandManager::freeInstance(){
	SDL_LockMutex(mxInstance);	// Locks the mutex...
	if (pUniqueInstance != NULL) {
        delete pUniqueInstance;
        pUniqueInstance = NULL;
    }
 	SDL_UnlockMutex(mxInstance);	// Unlocks the mutex...
}

void CommandManager::setServer(Server* myServer){
	SDL_LockMutex(mxServer);
	this->myServer = myServer;		// Sets the CommandManager Server.
	this->myScheduler->setServer(myServer);
	SDL_UnlockMutex(mxServer);
}

void CommandManager::processCommand(std::string &cmd){
	std::string tmp;
	Uint16 epos;
	ICommand* cmdObj = NULL;    // This will be deleted by CommandScheduler.

	// Finds the command
	tmp = cmd;
	epos = tmp.find(" ");
	tmp.assign(tmp,0,epos);

	// Commands switch. This could be delegated to a parser class.
	// Please keep alphabetical order.
	if (tmp.size() == 0) // Empty message or white space at the beginning.
		std::cout << "Please enter a command or clear white spaces before your command." << std::endl;
    else if ( tmp == "accounts" ){ // Account manager.
        cmdObj = new Cmd_accounts(cmd, myServer);
    }
    else if ( tmp == "chat" ){ // Basic chat interface for the console.
        cmdObj = new Cmd_chat(cmd, myServer);
    }
    else if ( tmp == "exit" || tmp == "quit" ){ // Quit command sent.
        cmdObj = new Cmd_exit(cmd, myServer);
    }
	else if (tmp == "test"){
		cmdObj = new Cmd_test(cmd, myServer);
	}
	else{ // Invalid or non-existent command.
		cmdObj = NULL;
		std::cout << "Command not found." << std::endl;
	}

	if(cmdObj != NULL){
		this->myScheduler->queue(cmdObj); // Queue the command.
	}
}

CommandManager::CommandManager()
	:mxServer(SDL_CreateMutex()),
	myScheduler(CommandScheduler::getInstance())
{
}

CommandManager::~CommandManager()
{
	SDL_DestroyMutex(mxServer);
}
