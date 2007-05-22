/*
 * Some code is taken from the mana world server project (http://themanaworld.org).
 */

#ifndef MESSAGEOUT_H_
#define MESSAGEOUT_H_

#include "crc32.h"

#include "Message.h"

class NetPacket;

using namespace std;
/**
 * A Message that will be sent trought network.
 * 
 * @todo TODO Comment the implementation.
 */
class MessageOut : public Message
{
public:

	/**
	 * Builds a message of a given type. Tipically used to create
	 * a new message that will be sent. For type definition see 
	 * Message.h .
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @param m_type Message's type. See above for definitions.
	 * @see Message.h
	 */
	MessageOut(const message_type m_type);
	
	/**
	 * Virtual destructor.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 */
	virtual ~MessageOut();
	
	/**
	 * Writes a single byte to myData.
	 * 
	 * @author themanaworld
	 * @author stonedz
	 * @since pre-alpha
	 * @param value Byte to write. 
	 */
	void write1(char value);
	
	/**
	 * Writes an unsigned 2 byte integer to myData.
	 * 
	 * The data written are in Network Byte Order.
	 * 
	 * @author themanaworld
	 * @author stonedz
	 * @since pre-alpha
	 * @param value 2 bytes to write.
	 * @todo TODO Check for other than x86 compatibility.
	 */          
    void write2(Uint16 value);
      
    /**
     * Writes an unsigned 4 byte integer to myData.
     * 
     * The data written are in Network Byte Order.
     * 
     * @author themanaworld
     * @author stonedz
     * @since pre-alpha
     * @param value 4 bytes to write.
     * @todo TODO Check for other than x86 compatibility.
     */      
    void write4(Uint32 value);
    
    /**
     * Returns current message's data.
     * 
     * @author stonedz
     * @since pre-alpha
     * @return Pointer to current message's data.
     */
    char* getData();
    
    /**
     * Returns current data's lenght.
     * 
     * @author stonedz
     * @since pre-alpha
     * @return Lenght in bytes.
     */
    Uint32 getDataSize();
    
    /**
     * Return a packed built from this message.
     * 
     * WARNING: Modifications to the message after a call to getPacket
     * won't be considered. The memory allocated for the packet is deleted
     * in message's destructor.
     * 
     * @author themanaworld
     * @author stonedz
     * @since pre-alpha
     * @return A pointer to a packet instance. 
     */
     const NetPacket* getPacket();
     
     /**
      * Writes a string to the message.
      * 
      * If the lenght parameter isn't specified, which is the default 
      * behaviur, string lenght will be automatically written on two
      * initial bytes. If you specify the lenght it means that you know 
      * what you're doing, because you will have to deal with a manual 
      * approach in message's building.
      * 
      * @author themanaworld
      * @author stonedz
      * @since pre-alpha
      * @param string Constant reference to the string we want to write.
      * @param lenght String lenght, if not specified it'll be calculated by this method.
      */
     void writeString(const string &string, Sint16 length = -1);
	
	/**
	 * Computes than add the CRC at message's bottom.
	 * 
	 * CRC is computed then added at the end of the message's payload. Since
	 * its lenght is fixed it (the lenght) will not be added to lenght message's field.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @return CRC value. 
	 */
	Uint32 addCRC();
	
private:
 
    /**
	 * Expands current allocated memory for myData using realloc.
	 * 
	 * WARNING: more memory may be allocated by realloc due to performance
	 * reasons.
	 * 
	 * @author themanaworld
	 * @author stonedz
	 * @since pre-alpha
	 * @param size The new size of the allocated memory, in bytes.
	 */
	void expandData(Uint16 size);

	char* myData;			/**< Current message's data. */
	Uint32 myDataSize;		/**< Current data's lenght. */
	Uint32 pos; 			/**< Pointer to current position in data. */
	NetPacket* myPacket; 	/**< A packet to be sent or received from network. */
};

#endif /*MESSAGEOUT_H_*/
