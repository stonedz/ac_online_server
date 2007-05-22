#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <iostream>

#include "SDL.h"
#include "SDL_thread.h"

class CommandManager;	// Forward declarations.
class Server;

using namespace std;

class Console; // forward declaration.

struct ConsoleData{
	Console* self;			/**< Pointer to self */
	string banner;			/**< Welcome message */
	SDL_Thread* myThread;	/**< Thread I'm running in */
	bool running;			/**< State of the console */
};
/**
 * Manages console-like interaction: accepts admin commands and performs
 * maintenance actions.
 * 
 * @todo Finish implementation.
 * @todo TODO Error handling.
 */
class Console
{
public:
	/**
	 * Constructor.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @param server A Server pointer to bind the console to.
	 */
	Console(Server * server);
	
	/**
	 * Virtual destructor.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 */
	virtual ~Console();
	
	/**
	 * It's a wrapper to use SDL's threads.
	 *
	 * This is because SDL_threads are written in pure C, and a function or 
	 * a static method is needed in order to create a thread. It passes the control
	 * to the startListen method
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @see startConsole
	 * @return The thread
	 */
	static int startThread(void * data);
	
	/**
	 * Starts the console.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 */
	void startConsole(ConsoleData  * data); 
	
	/**
	 * Sets the CommandManager's server.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @param myServer A valid Server pointer.
	 * @see cmdManager
	 * @todo TODO This is a bit tricky, we should change it.
	 */
	 void setServer(Server * myServer);
	
private:
	
	struct ConsoleData data;	/**< Contains console's data */
	CommandManager* cmdManager;	/**< Command manager. */
	
};

#endif /*CONSOLE_H_*/
