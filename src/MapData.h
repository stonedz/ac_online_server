#ifndef MAPDATA_H
#define MAPDATA_H

#include <fstream>
#include <iostream>

#include "SDL.h"

struct coord{
	Uint8 z;
	Uint8 t_type;	
};

/**
 * Represents the game's maps in memory.
 */
class MapData{
public:
    MapData(const Uint16& x, const Uint16& y,  std::ifstream* pFin);

    ~MapData();
	
	coord* myData;	/**< Map data */
	
	Uint16 getMaxX(){return myX;};
	
private :
	
	Uint16 myX;		/**< X width. */
	Uint16 myY;		/**< Y height */
	

};

#endif
