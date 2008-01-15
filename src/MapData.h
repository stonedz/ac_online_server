#ifndef MAPDATA_H
#define MAPDATA_H

#include "SDL.h"

struct coord{
	Uint32 x;
	Uint32 y;
	Uint32 z;
	bool walkable;
	bool see;	
};

/**
 * Represents the game's maps in memory.
 */
class MapData{
public:
    MapData();

    ~MapData();

};

#endif
