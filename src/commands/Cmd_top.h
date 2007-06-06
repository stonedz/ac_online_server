#ifndef CMD_TOP_H
#define CMD_TOP_H

#include "ICommandServer.h"
#include <iostream>
#include <iomanip>


/**
 * Command that shows server performances.
 */
class Cmd_top : public ICommandServer
{
    public:

        /**
         * Command that shows server performances.
         *
         * @author stonedz
         * @since
         * @param params Parameters passed to the command.
         * @param server The Server instance I'm running in.
         */
        Cmd_top(std::string &params, Server* server) : ICommandServer(params,server) {};

        virtual ~Cmd_top();

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
         * This commands calculates server's performances using data collected
         * in GameFSM class.
         *
         * @author stonedz
         * @since pre-alpha
         * @see perfLogShort
         * @see perfLogLong
         */
        void execute();

        /**
         * Prints detailed statistics of the server.
         *
         * @author stonedz
         * @since pre-alpha
         */
        void stats();

        /**
         * Prints a resume of the server's performance stats
         *
         * @author stonedz
         * @since pre-alpha
         */
        void resume();

};


#endif // CMD_TOP_H
