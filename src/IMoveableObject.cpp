#include "IMoveableObject.h"


IMoveableObject::IMoveableObject(Uint64 serial, Uint16 type)
    :IGameObject(serial, type),
    mDestPos(Location())
{
    //ctor
}

IMoveableObject::~IMoveableObject()
{
    //dtor
}

bool IMoveableObject::move(){
    if (mDestPos != getPosition()){
        setPosition(mDestPos); //we trust MapManager::validateMove()
        return true;
    }
    else
        return false;
}


