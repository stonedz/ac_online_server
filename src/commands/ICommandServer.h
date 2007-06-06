#ifndef ICOMMANDSERVER_H_
#define ICOMMANDSERVER_H_

#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>

#include "ICommand.h"
#include "Server.h"
#include "Console.h"

class Server;

/**
 * Represents a server command, that is a command that
 * will work on the server properties.
 */
class ICommandServer : public ICommand
{
public:
	ICommandServer(std::string &params, Server * server);
	virtual ~ICommandServer();

protected:
	Server* myServer;
};

#endif /*ICOMMANDSERVER_H_*/
