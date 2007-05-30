#ifndef CMD_CHAT_H
#define CMD_CHAT_H

#include "ICommandServer.h"

/**
 * Command to receive and send chat messages to the clients.
 */
class Cmd_chat : public ICommandServer
{
public:
    Cmd_chat(std::string &params, Server* server) : ICommandServer(params,server) {};

    virtual ~Cmd_chat();

    void help();

    void execute();
};



#endif // CMD_CHAT_H
