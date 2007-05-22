#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_thread.h>

#include "ConnectionData.h"

class ConnectionData; // Forward declarations.
class Message;
class MessageIn;
class MessageOut;
class NetPacket;

/**
 * Abstract class (interface) for a generic connection.
 *
 * @author stonedz
 * @since pre-alpha
 */
class Connection
{
public:
	/**
	 * Constructor for a generic connection.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 */
	Connection();

	/**
	 * Virtual destructor.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 */
	virtual ~Connection();

	/**
	 * Gets a NetPacket from network and then builds a Message
	 * that will be returned.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @param socket Socket to monitor.
	 * @return A MessageIn pointer. A NULL pointer means failure.
	 * @todo TODO Comment the implementation.
	 * @todo TODO Improve error handling.
	 */
	static MessageIn* getMessage(TCPsocket socket);

	/**
	 * Puts a Message to the given socket. It transforms the given Message
	 * into a NetPacket, then it sends the packet to the given socket.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @param socket Socket to send the message to.
	 * @param msg Message to be sent.
	 * @return Size of sent data. 0 (zero) means failure.
	 * @todo TODO Comment the implementation.
	 * @todo TODO Improve error handling.
	 */
	static Uint32 putMessage(TCPsocket socket, MessageOut* msg);

	/**
	 * Listening routine.
	 *
	 * This is what a Connection is supposed to do while running.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @param data Contains the connection's data.
	 */
	virtual void startListen(ConnectionData * data) = 0;

	/**
	 * It's a wrapper to use SDL's threads.
	 *
	 * This is because SDL_threads are written in pure C, and a function or
	 * a static method is needed in order to create a thread. It passes the control
	 * to the startListen method
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @param data A ConnectionData pointer.
	 * @see ConnectionData
	 * @see startListen
	 */
	static int startThread(void * data);

	/**
	 * Returns connection's thread. Useful to join threads.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @return Connection's thread.
	 */
	SDL_Thread* getThread();

	TCPsocket getSocket();

protected:

	ConnectionData* data; /**<  Contains data needed to start a thread.*/

};

#endif /*CONNECTION_H_*/
