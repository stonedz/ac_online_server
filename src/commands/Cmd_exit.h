#ifndef CMD_EXIT_H
#define CMD_EXIT_H

#include "ICommandServer.h"

/**
 * This command will close the server and then quit the application, in the future
 * parameters will be added in order to delay the shutdown and to display ingame
 * messages.
 */
class Cmd_exit : public ICommandServer
{
public:
    Cmd_exit(std::string &params, Server* server) : ICommandServer(params, server) {};

    virtual ~Cmd_exit();

    void help();

	void execute();
};



#endif // CMD_EXIT_H
