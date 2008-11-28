#include "Location.h"


Location::Location(Uint16 x, Uint16 y, Uint16 z)
    :mX(x),
    mY(y),
    mZ(z),
    mxCoords(SDL_CreateMutex())
{
    //ctor
}

Location::~Location()
{
    SDL_DestroyMutex(mxCoords);
}

Location& Location::operator= (const Location& l){
        if (this == &l) // Handle self-assignment.
            return *this;

        //Deletes eventual dyamic allocated memory here.
        SDL_DestroyMutex(mxCoords);     // I think that this is useless...
        mxCoords = SDL_CreateMutex();
        //Copy members.
        SDL_LockMutex(mxCoords);
        SDL_LockMutex(l.mxCoords);
        mX = l.mX;
        mY = l.mY;
        mZ = l.mZ;
        SDL_UnlockMutex(l.mxCoords);
        SDL_UnlockMutex(mxCoords);

        return *this;
}

bool Location::operator== (const Location& l)
{
	bool ret;

	if (this == &l)
	{
		return true;
	}

	ret = false;
	SDL_LockMutex(mxCoords);
    SDL_LockMutex(l.mxCoords);
	if (
		(mX == l.mX) &&
		(mY == l.mY) &&
		(mZ == l.mZ)
		)
	{
		ret = true;
	}
    SDL_UnlockMutex(l.mxCoords);
    SDL_UnlockMutex(mxCoords);

	return ret;
}

bool Location::operator!= (const Location& l)
{
	bool ret;

	if (this == &l)
	{
		return false;
	}

	ret = true;
    SDL_LockMutex(mxCoords);
    SDL_LockMutex(l.mxCoords);
	if (
		(mX == l.mX) &&
		(mY == l.mY) &&
		(mZ == l.mZ)
		)
	{
		ret = false;
	}
    SDL_UnlockMutex(l.mxCoords);
    SDL_UnlockMutex(mxCoords);

	return ret;
}
