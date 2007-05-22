#ifndef CHAR_H
#define CHAR_H

#include "IMoveableObject.h"
#include "SDL.h"

/**
 * Represents a playing character. This is only for a real player
 * chracter, NPC have their own class.
 */
class Char : public IMoveableObject
{
public:
    /**
     * Temporary constructor implementation. To be finished.
     *
     * @param serial A valid, unique serial.
     * @param type The object type.
     * @param dbId Database id of the character.
     */
    Char(Uint32 serial, Uint16 type, Uint32 dbId);

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

private:

    Uint32 myId;       /**< Character Database unique Id, this is NOT the serial. */

};



#endif // CHAR_H
