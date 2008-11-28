#ifndef LOCATION_H
#define LOCATION_H

#include <SDL/SDL.h>

/**
 * Represents a position in game. Thread safe.
 *
 * @todo Implement copy constructor.
 */
class Location
{
public:

    /**
     * Creates a new Location, if no arguments are specified we create
     * a 0,0,0 Location, wich is the invalid Location.
     */
    Location(Uint16 x = 0, Uint16 z = 0, Uint16 y = 0);

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
    Uint16 getX() { SDL_LockMutex(mxCoords);
                    Uint16 X = mX;
                    SDL_UnlockMutex(mxCoords);
                    return X;}

    /**
     * Sets the X coordinate.
     *
     * @author stonedz
     * @since pre-alpha
     * @param newX The new X coordinate.
     */
    void setX(Uint16 newX) {SDL_LockMutex(mxCoords);
                            mX = newX;
                            SDL_UnlockMutex(mxCoords);}

    /**
     * Returns the Y coordinate.0
     *
     * @author stonedz
     * @since pre-alpha
     * @return The Y coordinate of the Location.
     */
    Uint16 getY() { SDL_LockMutex(mxCoords);
                    Uint16 Y = mY;
                    SDL_UnlockMutex(mxCoords);
                    return Y;}

    /**
     * Sets the Y coordinate.
     *
     * @author stonedz
     * @since pre-alpha
     * @param newY The new Y coordinate.
     */
    void setY(Uint16 newY) {SDL_LockMutex(mxCoords);
                            mY = newY;
                            SDL_UnlockMutex(mxCoords);}

    /**
     * Returns the Z coordinate.
     *
     * @author stonedz
     * @since pre-alpha
     * @return The Z coordinate of the Location.
     */
    Uint16 getZ() { SDL_LockMutex(mxCoords);
                    Uint16 Z = mZ;
                    SDL_UnlockMutex(mxCoords);
                    return Z;}

    /**
     * Sets the Z coordinate.
     *
     * @author stonedz
     * @since pre-alpha
     * @param newZ The new Z coordinate.
     */
    void setZ(Uint16 newZ) {SDL_LockMutex(mxCoords);
                            mZ = newZ;
                            SDL_UnlockMutex(mxCoords);}

    /**
     * Sets the 3 coordinates X Y and Z.
     *
     * @author stonedz
     * @since pre-alpha
     * @param newX New X coordinate.
     * @param newY New Y coordinate.
     * @param newZ New Z coordinate.
     */
    void setXYZ(Uint16 newX, Uint16 newY, Uint16 newZ) {SDL_LockMutex(mxCoords);
                                                        mX = newX;
                                                        mY = newY;
                                                        mZ = newZ;
                                                        SDL_UnlockMutex(mxCoords);}

    /**
     * Returns the 3 coordinates X Y and Z.
     *
     * @author stonedz
     * @since pre-alpha
     * @param x Returned X coordinate.
     * @param y Returned Y coordinate.
     * @param z Returned Z coordinate.
     */
    void getXYZ(Uint16 &x, Uint16 &y, Uint16 &z) {  SDL_LockMutex(mxCoords);
                                                    x = mX;
                                                    y = mY;
                                                    z = mZ;
                                                    SDL_UnlockMutex(mxCoords);}
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

    Uint16 mX;          /**< My X coordinate. */
    Uint16 mY;          /**< My Y coordinate. */
    Uint16 mZ;          /**< My Z coordinate. */
    SDL_mutex* mxCoords;/**< Mutex to prevents concurrency during reading/writing of the coords. */
};



#endif // LOCATION_H
