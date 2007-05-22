#include "IGameObject.h"

#include "Location.h"

IGameObject::IGameObject(Uint32 serial, Uint16 type)
    :mSerial(serial),
    mType(type),
    mOwner(0),
    mName("Generic Object"),
    mPos(Location())
{
    //ctor
}

IGameObject::~IGameObject()
{

}

void IGameObject::setOwner(Uint32 newOwner){
    mOwner = newOwner;
}

void IGameObject::setName(std::string newName){
    mName = newName;
}
