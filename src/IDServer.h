#ifndef IDSERVER_H
#define IDSERVER_H

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
		IDServer();
		
		/**
		 * Virtual Destructor
		 */
		virtual ~IDServer();
};


#endif
