/*
 * Some code is taken from the mana world server project (http://themanaworld.org).
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <cstdlib>
#include <cstring>
#include <string>

#include <SDL/SDL_net.h>

#define MSG_INVALID (0)		/**< Invalid message. */
#define MSG_LOGIN 	(1)		/**< Login message, a client wants to authenticate. */
#define MSG_LOGOUT 	(2)		/**< Logout message, a client wants to quit. */
#define MSG_CHAT 	(3)		/**< Chat message, a normal (generic)  chat message.*/
#define MSG_KA		(4)		/**< Keep Alive message (client send this message).*/
#define MSG_KA_ACK	(5)		/**< Keep Alive ACK (server reply to KA with this message).*/
#define MSG_MOVE	(6)		/**< Movement message: from client to server requests a destination, from server to client allow a movement. */

/**
 * A new type to describe message's types -> two first
 * bytes of a message.
 */
typedef Uint16 message_type;

/**
 * Generic message. The data contained in the message is stored in
 * Network byte order.
 *
 * A message is composed by three parts:
 *
 * 	1) Message's type, 2 bytes, represents the message's type.
 *
 * 	2) Message's lenght, 2 bytes.
 *
 * 	3) Message's payload itself, the lenght is specified by previous part.
 *
 *  4) MEssage's CRC, 4 bytes.
 */
class Message
{
public:

	/**
	 * Builds a message.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 */
	 Message();

	/**
	 * Virtual destructor.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 */
	virtual ~Message();

};

#endif /*MESSAGE_H_*/
