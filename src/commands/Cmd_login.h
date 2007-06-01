#ifndef CMD_LOGIN_H
#define CMD_LOGIN_H

#include "ICommandServer.h"


/**
 * Command to login and test network messages.
 */
class Cmd_login : public ICommandServer
{
    public:
        /**
         * Command to login and test network messages.
         *
         * @author stonedz
         * @since pre-alpha
         * @param params Parameters passed to the command.
         * @param server The Server instance I'm running in.
         */
        Cmd_login(std::string &params, Server* server) : ICommandServer(params,server) {};

        virtual ~Cmd_login();

        /**
         * Prints a brief help message for the command.
         *
         * @author stonedz
         * @since pre-alpha
         */
        void help();

        /**
         * Execute the command.
         *
         * This command performs a connection to the server it's running in
         * and then stays alive for 10 seconds approx.
         *
         * @author stonedz
         * @since pre-alpha
         */
        void execute();

};



#endif // CMD_LOGIN_H
