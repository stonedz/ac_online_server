#ifndef IDSERVER_H
#define IDSERVER_H

#include "SDL.h"
#include "defs.h"
#include "Logger.h"
#include "Server.h"

/**
 * Manages the objects' uniques IDs.
 * 
 * Every Game object has an unique ID , this class creates the new ones when requested.
 * Thread safe
 */
class IDServer{
	public:
		/**
		 * Ctor
		 * 
		 * Initializes
		 */
		IDServer(Server* server);
		
		/**
		 * Virtual Destructor
		 */
		virtual ~IDServer();
		
		/**
		 * Creates a new ID
		 * 
		 * @author stonedz
		 * @since pre-alpha
		 * @param type the Game Object type, see defines in defs.h files.
		 */
		Uint64 getNewId(const Uint8& type);
		
		/**
		 * Update time slice
		 * 
		 * @author stonedz
		 * @since pre-alpha
		 * @see myTime
		 * @return New Time slice.
		 */
		Uint32 updateTime();
		
	private:
		Uint32 myTime;		/**< Current time */
		Uint32 myObjNum;
		Server* myServer;	/**< reference to the server I'm running in.*/
};


#endif
