#include "IGameObject.h"

#include "Location.h"
#include "SDL.h"

IGameObject::IGameObject(Uint64 serial, Uint16 type)
    :mSerial(serial),
    mType(type),
    mOwner(0),
    mName("Generic Object"),
    mPos(Location()),
    mxPos(SDL_CreateMutex()),
    mxOwner(SDL_CreateMutex()),
    mxName(SDL_CreateMutex())
{
    //ctor
}

IGameObject::IGameObject(Uint16 type)
		
{
	//ctor
}

IGameObject::~IGameObject()
{
    // Delete mutexes.
    SDL_DestroyMutex(mxPos);
    SDL_DestroyMutex(mxOwner);
    SDL_DestroyMutex(mxName);
}

void IGameObject::setOwner(Uint32 newOwner){
    SDL_LockMutex(mxOwner);
    mOwner = newOwner;
    SDL_UnlockMutex(mxOwner);
}

void IGameObject::setName(const std::string& newName){
    SDL_LockMutex(mxName);
    mName = newName;
    SDL_UnlockMutex(mxName);
}
