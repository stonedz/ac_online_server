#ifndef CMD_TEST_H_
#define CMD_TEST_H_

#include <iostream>

#include "ICommandServer.h"


class Server;

/**
 * This is a command to test the command system.
 */
class Cmd_test : public ICommandServer
{
public:
    Cmd_test(std::string &params, Server* server) : ICommandServer(params, server) {};

	virtual ~Cmd_test();

	void help();

	void execute();
};

#endif /*CMD_TEST_H_*/
