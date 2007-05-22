#include <iostream>
#include <string>
#include "Console.h"
#include "CommandManager.h"

Console::Console(Server * server)
	:cmdManager(CommandManager::getInstance())
{
	this->data.self = this;
	this->data.running = true;
	this->data.banner = "\n:: Welcome to Last Online ::\n\npre-alpha version\nPlease refer to http://last-online.sourceforge.net for more informations.";

	this->data.myThread = SDL_CreateThread(this->startThread, &(this->data));

	this->cmdManager->setServer(server);	// Sets the Command Manager server.
}

Console::~Console()
{
}

int Console::startThread(void * data){
	ConsoleData * trueData =  reinterpret_cast<ConsoleData *>(data);
	trueData->self->startConsole(trueData);

	return 1;
}

void Console::startConsole(ConsoleData * data){
		bool exit = false;

		std::string selection;
		std::cout << data->banner.c_str() << std::endl;
		do{
			std::cout << std::endl << "> ";
			std::getline(std::cin, selection);
			this->cmdManager->processCommand(selection);
		}while(!exit);
}

void Console::setServer(Server* myServer){
	this->cmdManager->setServer(myServer); // Sets the CommandManager's Server.
}
