#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "MapData.h"
#include "Location.h"
#include <iostream>


/**
 * Manages a game map. This is still work in rpogress since we've not decided how to
 * implement it. Implements the Sinlgeton pattern.
 *
 * @todo Design, see #15
 * @todo Should be Thread safe
 */
class MapManager
{
protected:
        /**
         * Creates an empty MapManager.
         *
         */
	MapManager();

        /**
         * Virtual destructor.
         */
	virtual ~MapManager();

public:
	/**
	 * Gets the mapmanager. Since this class implements
	 * the Singleton pattern, this method is the one to be called
	 * to get an usable instance.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @return The MapManager instance.
	 */
	static MapManager* getInstance();

	/**
	 * Frees the MapManager instance and its memory.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 */
	static void freeInstance();
private:

	static MapManager* pUniqueInstance;	/**< MapManager instance. */
	static SDL_mutex* mxInstance;		/**< Instance mutex, for thread safetyness. */

public:
	/**
	 * Loads an XML map with "filneame.xml" name.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @param filename XML file name , without the XML extension.
	 * @return True if the map is correctly load, false elsewhere.
	 * @todo This is WORK IN PROGRESS!
	 */
	bool loadXMLMap(const std::string& filename);
	
	
	/**
	 * Loads the main terrain map
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @param filename Complete map filename.
	 * @return True if the map is correctly loaded, false elsewhere.
	 * @todo This is WORK IN PROGRESS
	 */
	bool loadBinTMap(const std::string& filename);
	
	/**
	 * Validates a Location on the map
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @param loc Reference to the Location object to validate.
	 * @return True if the Location is valid, false elsewhere.
	 */
	//bool validateLocation(Location& loc);
	
	/**
	 * Validates an object's movement.
	 *
	 * This is used to validate a movement, and to avoid objects moving into unwanted zones.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @return True if the move is valid, false elsewhere.
	 * @todo Find a better algorithm to evaluate valid movement.
	 */
	bool validateMove(Location& orig, Location& dest);
	
	/**
	 * Returns a coord struct for the given coordinates
	 * 
	 * @author stonedz
	 * @param x
	 * @param y
	 * @since pre-alpha
	 */
	coord getInfo(const Uint16& x, const Uint16& y);

private:
	MapData* myTMap;
};



#endif // MAPMANAGER_H
