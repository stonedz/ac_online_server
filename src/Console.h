#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <iostream>
#include <sstream>

#include "SDL.h"
#include "SDL_thread.h"
#include "defs.h"

#ifdef LINUX
#ifdef WITH_COLORS
#include "utils/linux/Console_linux.h"
#else
#include "utils/Console_no_colors.h"
#endif
#endif

#ifdef WINDOWS
#ifdef WITH_COLORS
#include "utils/windows/Console_windows.h"
#else
#include "utils/Console_no_colors.h"
#endif
#endif


class CommandManager;	// Forward declarations.
class Server;

using namespace std;

class Console; // forward declaration.

struct ConsoleData{
	Console* self;			    	/**< Pointer to self */
	std::ostringstream banner;	/**< Welcome message */
	SDL_Thread* myThread;	    	/**< Thread I'm running in */
	bool running;			    	/**< State of the console */
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

	 /**
	  * Prints a generic message to the console, without disturbing the console itself.
	  *
	  * @author stonedz
	  * @since pre-alpha
	  * @param msg Message to print.
	  * @param mode Mode to print the message.
	  */
    void printMsg(const std::string& msg, Uint16 mode = CONSOLE_INFO);

    /**
     * Prints a generic message to the console, without disturbing the console itself.
     *
     * @author stonedz
     * @since pre-alpha
     * @param msg Message to print.
     * @param mode Mode to print the message.
     */
    void printMsg(const std::ostringstream& msg, Uint16 mode = CONSOLE_INFO);

private:

	struct ConsoleData data;	        /**< Contains console's data */
	CommandManager* cmdManager;	        /**< Command manager. */
	SDL_mutex* mxMsgQueue;              /**< Mutex to avoid problems during printing to the console. */

};

#endif /*CONSOLE_H_*/
