#ifndef LOCATION_H
#define LOCATION_H

#include <SDL/SDL.h>

/**
 * Represents a position in game.
 */
class Location
{
public:

    /**
     * Creates a new Location, if no arguments are specified we create
     * a 0,0,0 Location, wich is the invalid Location.
     */
    Location(Uint32 x = 0, Uint32 z = 0, Uint32 y = 0);

    /**
     * Virtual destructor.
     */
    virtual ~Location();

    /**
     * Returns the X coordinate.
     *
     * @author stonedz
     * @since pre-alpha
     * @return The X coordinate of the Location.
     */
    Uint32 getX() {return mX;}

    /**
     * Sets the X coordinate.
     *
     * @author stonedz
     * @since pre-alpha
     * @param newX The new X coordinate.
     */
    void setX(Uint32 newX) {mX = newX;}

    /**
     * Returns the Y coordinate.0
     *
     * @author stonedz
     * @since pre-alpha
     * @return The Y coordinate of the Location.
     */
    Uint32 getY() {return mY;}

    /**
     * Sets the Y coordinate.
     *
     * @author stonedz
     * @since pre-alpha
     * @param newY The new Y coordinate.
     */
    void setY(Uint32 newY) {mY = newY;}

    /**
     * Returns the Z coordinate.
     *
     * @author stonedz
     * @since pre-alpha
     * @return The Z coordinate of the Location.
     */
    Uint32 getZ() {return mZ;}

    /**
     * Sets the Z coordinate.
     *
     * @author stonedz
     * @since pre-alpha
     * @param newZ The new Z coordinate.
     */
    void setZ(Uint32 newZ) {mZ = newZ;}

    /**
     * Sets the 3 coordinates X Y and Z.
     *
     * @author stonedz
     * @since pre-alpha
     * @param newX New X coordinate.
     * @param newY New Y coordinate.
     * @param newZ New Z coordinate.
     */
    void setXYZ(Uint32 newX, Uint32 newY, Uint32 newZ) {mX = newX;
                                                        mY = newY;
                                                        mZ = newZ;}

    /**
     * Returns the 3 coordinates X Y and Z.
     *
     * @author stonedz
     * @since pre-alpha
     * @param x Returned X coordinate.
     * @param y Returned Y coordinate.
     * @param z Returned Z coordinate.
     */
    void getXYZ(Uint32 &x, Uint32 &y, Uint32 &z) {x = mX;
                                                  y = mY;
                                                  z = mZ;}
    /**
     * Redefines the assignment operator.
     *
     * @author stonedz
     * @since pre-alpha
     */
    Location& operator=(const Location& l);

	/**
	 * Redefines the equality operator (==)
	 *
	 * @author dndvault
	 * @since pre-alpha
	 */
	bool operator==(const Location &l);
	bool operator!=(const Location &l);

private:

    Uint32 mX;  /**< My X coordinate. */
    Uint32 mY;  /**< My Y coordinate. */
    Uint32 mZ;  /**< My Z coordinate. */
};



#endif // LOCATION_H
