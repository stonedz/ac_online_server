#ifndef COMMANDSCHEDULER_H_
#define COMMANDSCHEDULER_H_

#include <iostream>

#include "SDL.h"

#include "commands/ICommand.h"

class Server;

/**
 * Schedules and executes commands.
 */
class CommandScheduler
{
public:

	/**
	 * Returns class' instance.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @return Class' instance.
	 */
	static CommandScheduler* getInstance();
	
	/**
     * Deletes the class's instance.
     * 
     * @author stonedz
     * @since pre-alpha
     */
    static void freeInstance();
       
    /**
     * Sets the Server the CommandScheduler refers to.
     * 
     * @author stonedz
     * @since pre-alpha
     * @param myServer A valid Server pointer.
     */
    void setServer(Server* myServer);
    
    /**
     * Queues commands and executes them.
     * 
     * In the final implementation this method will queue commands
     * and then schedule them for execution. As for now, it executes
     * the command.
     * 
     * @author stonedz
     * @since pre-alpha
     * @param cmd The ICommand to queue.
     * @todo TODO Finish the implementation.
     */
    void queue(ICommand* cmd);
    
private:

	static CommandScheduler* pUniqueInstance;	/**< Reference to unique CommandScheduler instance. */
	static SDL_mutex* mxInstance;				/**< Instance mutex, for thread safetyness. */
    Server* myServer;							/**< Points to a valid Server. */
    SDL_mutex* mxServer;						/**< Server's mutex. */
    
protected:

	CommandScheduler();
	virtual ~CommandScheduler();
};

#endif /*COMMANDSCHEDULER_H_*/
