#ifndef CONNECTIONDATA_H_
#define CONNECTIONDATA_H_

#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_thread.h>

class Connection;

/**
 * Contains useful data for a generic connection.
 * 
 * It is mainly used to create a new thread for the Connection.
 * 
 * @author stonedz
 * @since pre-alpha
 * @see startListen
 */
class ConnectionData
{
public:
	/**
	 * Constructor.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 */
	ConnectionData();
	
	/**
	 * Virtual destructor.
	 */
	virtual ~ConnectionData();
	
	TCPsocket socket;		/**< Connection's TCP socket.*/
	SDL_Thread* thread; 	/**< Pointer to the thread the connection is running in.*/
	Connection* self; 		/**< Pointer to itself.*/
	bool running; 			/**< State of the connection.*/
	IPaddress address;		/**< Address and port of the server.*/
	
	/**
	 * Unique id of the connection.
	 * 
	 * @todo TODO To be implemented -> Implements a thread-safe id-generator.
	 */
	Uint32 id;
};

#endif /*CONNECTIONDATA_H_*/
