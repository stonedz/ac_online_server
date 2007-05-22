#include "Location.h"


Location::Location(Uint32 x, Uint32 y, Uint32 z)
    :mX(x),
    mY(y),
    mZ(z)
{
    //ctor
}

Location::~Location()
{
    //dtor
}

Location& Location::operator= (const Location& l){
        if (this == &l) // Handle self-assignment.
            return *this;

        //Deletes eventual dyamic allocated memory here.

        //Copy members.
        mX = l.mX;
        mY = l.mY;
        mZ = l.mZ;

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
	if (
		(mX == l.mX) &&
		(mY == l.mY) &&
		(mZ == l.mZ)
		)
	{
		ret = true;
	}

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
	if (
		(mX == l.mX) &&
		(mY == l.mY) &&
		(mZ == l.mZ)
		)
	{
		ret = false;
	}

	return ret;
}
