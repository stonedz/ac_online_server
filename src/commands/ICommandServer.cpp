#include "ICommandServer.h"


ICommandServer::ICommandServer(std::string &params, Server * server)
	:ICommand(params),
	myServer(server)
{
}

ICommandServer::~ICommandServer()
{
}
