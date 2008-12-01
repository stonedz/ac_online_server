#ifndef CMD_TEST_H_
#define CMD_TEST_H_

#include <iostream>

#include "ICommandServer.h"


class Server;

/**
 * This is a command to test the command system.
 * It could be used to test some sever internals.
 */
class Cmd_test : public ICommandServer
{
public:
    Cmd_test(std::string &params, Server* server) : ICommandServer(params, server) {};

	virtual ~Cmd_test();

	void help();

	void execute();

private:

    /**
     * Tests the movement and its validation.
     *
     * @author stonedz
     * @since pre-alpha
     * @see validateMove
     */
    void test_move();

    void test_location();
	
	void test_id();

};

#endif /*CMD_TEST_H_*/
