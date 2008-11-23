#include <iostream>
#include <string>
#include "Console.h"
#include "CommandManager.h"

Console::Console(Server * server)
	:cmdManager(CommandManager::getInstance()),
	mxMsgQueue(SDL_CreateMutex())
{
	this->data.self = this;
	this->data.running = true;
    this->data.banner << std::endl << colors::blue << ":: "<< colors::green << "Welcome to Ancient Chronicles online" << colors::blue << " ::"
                    << std::endl << ":: " << colors::cyan << std::setw(36) << SERVER_VERSION << colors::blue << " ::"<< colors::reset
                    << std::endl << std::endl << "Please refer to " << colors::cyan << "http://www.assembla.com/spaces/aconlineserver" << colors::reset
                    << " for more informations.";

	this->data.myThread = SDL_CreateThread(this->startThread, &(this->data));

	this->cmdManager->setServer(server);	// Sets the Command Manager server.
}

Console::~Console()
{
    //SDL_DestroyMutex(mxMsgQueue);
}

int Console::startThread(void * data){
	ConsoleData * trueData =  reinterpret_cast<ConsoleData *>(data);
	trueData->self->startConsole(trueData);

	return 1;
}

void Console::startConsole(ConsoleData * data){
		bool exit = false;

		std::string selection;
		std::cout << data->banner.str() << std::endl;
		do{
		    SDL_LockMutex(mxMsgQueue);
			std::cout << std::endl << "> ";
			SDL_UnlockMutex(mxMsgQueue);
			std::getline(std::cin, selection);
			this->cmdManager->processCommand(selection);
		}while(!exit);
}

void Console::setServer(Server* myServer){
	this->cmdManager->setServer(myServer); // Sets the CommandManager's Server.
}

void Console::printMsg(const std::string& msg, Uint16 mode){

    if (mode == CONSOLE_INFO){
        SDL_LockMutex(mxMsgQueue);
        std::cout << colors::grey << "[Info] " <<  msg << colors::reset << std::endl << "> ";
        SDL_UnlockMutex(mxMsgQueue);
    }
    else if (mode == CONSOLE_WARNING){
        SDL_LockMutex(mxMsgQueue);
        std::cout << colors::magenta << "[Warning] " <<  msg << colors::reset << std::endl << "> ";
        SDL_UnlockMutex(mxMsgQueue);
    }
    else if (mode == CONSOLE_ERROR){
        SDL_LockMutex(mxMsgQueue);
        std::cout << colors::red << "[ERROR] " <<  msg << colors::reset << std::endl << "> ";
        SDL_UnlockMutex(mxMsgQueue);
    }
    else if (mode == CONSOLE_DEBUG){
        SDL_LockMutex(mxMsgQueue);
        std::cout << colors::grey << "[Debug] " <<  msg << colors::reset << std::endl << "> ";
        SDL_UnlockMutex(mxMsgQueue);
    }
}

void Console::printMsg(const std::ostringstream& msg, Uint16 mode){

    if (mode == CONSOLE_INFO){
        SDL_LockMutex(mxMsgQueue);
        std::cout << colors::grey  <<"[Info] " <<  msg.str() <<  colors::reset << std::endl << "> ";
        SDL_UnlockMutex(mxMsgQueue);
    }
    else if (mode == CONSOLE_WARNING){
        SDL_LockMutex(mxMsgQueue);
        std::cout << colors::magenta << "[Warning] " <<  msg.str() << colors::reset << std::endl << "> ";
        SDL_UnlockMutex(mxMsgQueue);
    }
    else if (mode == CONSOLE_ERROR){
        SDL_LockMutex(mxMsgQueue);
        std::cout << colors::red << "[ERROR] " <<  msg.str() << colors::reset << std::endl << "> ";
        SDL_UnlockMutex(mxMsgQueue);
    }
    else if (mode == CONSOLE_DEBUG){
        SDL_LockMutex(mxMsgQueue);
        std::cout << colors::grey << "[Debug] " <<  msg.str() << colors::reset << std::endl << "> ";
        SDL_UnlockMutex(mxMsgQueue);
    }
}
