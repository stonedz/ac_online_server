#include "IMoveableObject.h"


IMoveableObject::IMoveableObject(Uint32 serial, Uint16 type)
    :IGameObject(serial, type),
    mDestPos(Location())
{
    //ctor
}

IMoveableObject::~IMoveableObject()
{
    //dtor
}

void IMoveableObject::move(){
    if (mDestPos != getPosition())
        setPosition(mDestPos); // Teletransport ! not for production use :D
}


