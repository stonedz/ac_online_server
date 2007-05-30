#ifndef CMD_LOGIN_H
#define CMD_LOGIN_H

#include "ICommandServer.h"
/**
 * Command to login and test network messages.
 */
class Cmd_login : public ICommandServer
{
    public:
    Cmd_login(std::string &params, Server* server) : ICommandServer(params,server) {};

    virtual ~Cmd_login();

    void help();

    void execute();

};



#endif // CMD_LOGIN_H
