#ifndef CHAR_H
#define CHAR_H

#include "IMoveableObject.h"
#include "SDL.h"

class Client; //Forward declaration.

/**
 * Represents a playing character. This is only for a real player
 * chracter, NPC have their own class.
 */
class Char : public IMoveableObject
{
public:
    /**
     * Constructs a Game character.
     *
     * This is the last step in order to activate a Client,
     * if everything is ok then we can add the Client to the mClients
     * map of active clients.
     *
     * @param serial A valid, unique serial.
     * @param type The object type.
     * @param dbId Database id of the character.
     * @param client Reference to the Client which owns this Char
     */
    Char(Uint64 serial, Uint16 type, Uint32 dbId, Client& client);

    /**
     * Virtual destructor.
     */
    virtual ~Char();

    /**
     * Updates the char.
     *
     * @author stonedz
     * @since pre-alpha
     * @todo To be implemented.
     */
    void update();

    /**
     * Saves the char to database.
     *
     * @author stonedz
     * @since pre-alph
     */
    void save();

private:

    Uint32 myId;        /**< Character Database unique Id, this is NOT the serial. */
    Client& myClient;   /**< Reference to my Client. */

};



#endif // CHAR_H
