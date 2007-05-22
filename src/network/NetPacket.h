#ifndef NETPACKET_H_
#define NETPACKET_H_

#include <SDL/SDL.h>

#include "Packet.h"

/**
 * Represents a packet that will successively be sent trought
 * network.
 */
class NetPacket : public Packet
{
public:

	/**
	 * Constructs a packet that will be sent throught a Connection.
	 * 
	 * The data passed as the first parameter of this constructor must 
	 * have been previuosly prepared. This ensure abstraction from
	 * the network protocol we will choose.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @param data Pre-formatted data as a char array.
	 * @param lenght Data lenght.
	 */
	NetPacket(const char *data, Uint32 size);
	
	/**
	 * Returns current packet's data.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @deprecated
	 */
	char* getData();
	
	/**
	 * Cleans memory and destroys packet.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 */ 
	virtual ~NetPacket();
	
	char *data;	/**< Packet's data */        
    Uint32 len;	/** Packet's lenght. */
	
};

#endif /*NETPACKET_H_*/
