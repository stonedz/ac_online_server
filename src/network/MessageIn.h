/*
 * Some code is taken from the mana world server project (http://themanaworld.org).
 */

#ifndef MESSAGEIN_H_
#define MESSAGEIN_H_

#include "Message.h"

class NetPacket;


/**
 * Message built from a given packet. Usually it is an inbound
 * Message sent from a remote host.
 */
class MessageIn : public Message
{
public:

	/**
	 * Builds a message from a given packet. Tipically used to
	 * manage a received packet.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @param packet Packet to build the message from.
	 */
	MessageIn(NetPacket* packet);
	
	/**
	 * Virtual destructor.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 */
	virtual ~MessageIn();
	
	/**
	 * Returns the type of the message. for type definitions see
	 * Message.h.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @return Message type.
	 * @see Message.h
	 */
	message_type getType() { return myType; }
	
	/**
	 * Reads a single byte from the packet.
	 * 
	 * @author themanaworld
	 * @author stonedz
	 * @since pre-alpha
	 * @return The byte read. 0 if error.
	 */
    char read1();
    
    /**
     * Reads 2 bytes from packet.
     * 
     * Bytes are transformed from Network Byte Order to Little Endian.
     * 
     * @author themanaworld
     * @author stonedz
     * @since pre-alpha
     * @return The two bytes read. 0 if error.
	 * @todo TODO Check for other than x86 compatibility.
     */
    Uint16 read2();
    
    /**
     * Reads 4 bytes from packet.
     * 
     * Bytes are transformed from Network Byte Order to Little Endian.
     * 
     * @author themanaworld
     * @author stonedz
     * @since pre-alpha
     * @return The four bytes read. 0 if error.
	 * @todo TODO Check for other than x86 compatibility.
     */    
    Uint32 read4();
	
	/**
	 * Reads and returns message's CRC.
	 * 
	 * Bytes are transformed from Network Byte Order to Little Endian.This method 
	 * MUST be called after any other read method. It will usually be used after a readString()
	 * call.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @return Uint32 CRC, 0 if error.
	 * @todo TODO Check for other than x86 compatibility.
	 * @see readString
	 */
	 Uint32 getCRC();
	 
	/**
	 * Check the message crc against crc calculated locally.
	 * 
	 * @author dndvault
	 * @since pre-alpha
	 * @return True if ok, false if CRCs are different.
	 */
	 bool checkCRC();
		
	/**
	 * Reads a string from the message, if the lenght is not given
	 * then it retrieves string's lenght from the first two bytes of the message.
	 * 
	 * It's usually the unique method used to get message's body.
	 * 
	 * @author themanaworld
	 * @author stonedz
	 * @since pre-alpha
	 * @param lenght  String's lenght to read.
	 * @return The string read if ok, an empty string if fail. 
	 * @see getCRC
	 */
	std::string readString(Sint16 length = -1);
	
	/**
	 * Resets current message and deletes the packet associated with it.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 */
	void reset();
	
private:
	Uint32 pos; 			/**< Current position in the packet. */
    NetPacket *myPacket;	/**< The packet the message is built on. */
    message_type myType;	/**< Message type. */
};

#endif /*MESSAGEIN_H_*/
