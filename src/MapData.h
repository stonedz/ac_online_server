#ifndef MAPDATA_H
#define MAPDATA_H

#include "SDL.h"

struct coord{
	Sint8 z;
	Uint16 t_type;	
};

/**
 * Represents the game's maps in memory.
 */
class MapData{
public:
    MapData();

    ~MapData();
private :
	coord** Data;

};

#endif
