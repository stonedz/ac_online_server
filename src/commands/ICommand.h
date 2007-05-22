#ifndef ICOMMAND_H_
#define ICOMMAND_H_

#include <iostream>

#include "SDL.h"

class Server;

class ICommand
{
public:
	/**
	 * Construct a command given the command and all its parameters.
	 */
	ICommand(std::string &params);
	
	/**
	 * Virtual destructor
	 */
	virtual ~ICommand();
	
	/**
	 * Provides istuctions on how to use the command. This pure 
	 * virtual method has to be implemented in every command.
	 */
	virtual void help() = 0;
	
	/**
	 * Excutes the command. This pure virtual method has to be
	 * implemented in every command.
	 */
	virtual void execute() = 0;
	
protected:
	/**
	 * Gets the specified parameter where 1 (one) is the first parameter 
	 * after the command name. If toTheEnd is set to true this method will return
	 * the whole string after the specified parameter. 
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @param param the parameter we want to retrieve.
	 * @param toTheEnd if we want or not the whole string.
	 * @return The parameter(s) in a std::string form.
	 * @todo TODO Shouldn't we implement an Utils class to gather all this kind of tools?
	 */
	std::string getParam(Uint16 param, bool toTheEnd = false);
	
	std::string myParameters;	/**< Contains all the command line */
};

#endif /*ICOMMAND_H_*/
