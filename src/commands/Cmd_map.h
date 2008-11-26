//
// C++ Interface: Cmd_map
//
// Description: Command to test map management
//
//
// Author: Paolo Fagni, Alessandro Sperindé, Davide Bardone <paolo.fagni@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef CMD_MAP_H_
#define CMD_MAP_H_

#include <iostream>
#include <fstream>

#include "ICommandServer.h"

class Server;

/**
 * Command to test map management
 */
class Cmd_map : public ICommandServer{
	public:
		Cmd_map(std::string &params, Server* server) : ICommandServer(params, server) {};

		virtual ~Cmd_map();

		void help();

		void execute();

	private:
		
		/**
		 * Creates a dummy map with given filename in the current directory.
		 * 
		 */
		void create(const std::string& filename);
		
};

#endif /*CMD_MAP_H_*/
