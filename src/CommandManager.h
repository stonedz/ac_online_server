#ifndef COMMANDMANAGER_H_
#define COMMANDMANAGER_H_

#include <iostream>
#include <map>

#include "SDL.h"

class Server;			// Forward declarations.
class CommandScheduler;

/**
 * Manages server commands. 
 * 
 * CommandManager takes care of creating ICommand objects that will
 * be sent to the CommandScheduler for execution. In order to be 
 * fully functional, the CommandManager should have
 * a pointer to a valid server. This class implements Singleton pattern and
 * should be thread-safe.
 */
class CommandManager
{
public:
	/**
	 * Returns class' instance.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @return Class' instance.
	 */
	static CommandManager* getInstance();
	
	/**
     * Deletes the class's instance.
     * 
     * @author stonedz
     * @since pre-alpha
     */
    static void freeInstance();
    
    /**
     * Sets the Server the CommandManager refers to.
     * 
     * @author stonedz
     * @since pre-alpha
     * @param myServer A valid Server pointer.
     */
    void setServer(Server* myServer);
    
     /**
      * Processes a command received as a string.
      * 
      * It takes the whole command string, creates a new ICommand
      * command and then sends it to the CommandScheduler.See the 
      * dedicated documentation for further informations.
      * 
      * @author stonedz
      * @since pre-alpha
      * @param cmd The whole command string (parameters included).
      */
     void processCommand(std::string &cmd);

protected:
	/**
	 * Constructor.
	 */
	CommandManager();
	
	/**
	 * Virtual destructor.
	 */
	virtual ~CommandManager();
	
private:
	static CommandManager* pUniqueInstance;	/**< Reference to unique CommandManager instance. */
	static SDL_mutex* mxInstance;			/**< Instance mutex, for thread safetyness. */
	SDL_mutex* mxServer;					/**< Server's mutex. */
	Server* myServer;						/**< Points to a valid Server. */
	CommandScheduler* myScheduler;			/**< Pointer of a CommandScheduler. */
};

#endif /*COMMANDMANAGER_H_*/
