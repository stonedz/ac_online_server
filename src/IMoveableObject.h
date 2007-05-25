#ifndef IMOVEABLEOBJECT_H
#define IMOVEABLEOBJECT_H

#include "IGameObject.h"
#include "SDL.h"

/**
 * Abstract interface for moveable objects (items, NPC, PC).
 */
class IMoveableObject : public IGameObject
{
public:
    /**
     * Cosntructor
     */
    IMoveableObject(Uint32 serial, Uint16 type);

    /**
     * Virtual destructor.
     */
    virtual ~IMoveableObject();

    /**
     * Sets the destination position with a Location object pointer. Not thread safe.
     *
     * @author stonedz
     * @since pre-alpha
     * @param dest The new object's destination.
     */
    void setDestination(Location * dest) {mDestPos = *dest;}

    /**
     * Sets the destination position with a Location object reference. Not thread safe.
     *
     * @author stonedz
     * @since pre-alpha
     * @param dest The new object's destination.
     */
    void setDestination(const Location & dest) {mDestPos = dest;}

    /**
     * Moves the object towards its destination.
     *
     * @todo Temporary implementation, teleports to the destination Location
     * @see mDestPos
     */
    void move();

private:

    Location mDestPos;      /**< Where am I going to? */
};



#endif // IMOVEABLEOBJECT_H
