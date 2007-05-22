#include "Cmd_exit.h"

Cmd_exit::~Cmd_exit()
{
}

void Cmd_exit::help(){
    std::cout << "Ask the server to quit, further parameters will be added in the future." << std::endl;
}

void Cmd_exit::execute(void){
    this->myServer->requestExit();  // Sends a shutdown request to the server.
}



