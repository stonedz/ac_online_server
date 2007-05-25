#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "Location.h"

/**
 * Manages a game map. This is still work in rpogress since we've not decided how to
 * implement it.
 *
 * @todo Design
 */
class MapManager
{
    public:
        /**
         * Creates an empty MapManager.
         *
         * This is pretty useless at the moment, since the whole map management system has to be designed.
         * A MapManager object is solely used to test and validate movements.
         */
        MapManager();

        /**
         * Virtual destructor.
         */
        virtual ~MapManager();

        /**
         * Validates an object movement.
         *
         * This is used to validate a movement, and to avoid objects moving into unwanted zones.
         *
         * @author stonedz
         * @since pre-alpha
         * @return True if the move is valid, false elsewhere.
         * @todo Don't like pointers here...try to pass it as const.
         * @todo Find a better algorithm to evaluate valid movement.
         */
        bool validateMove(Location& orig, Location& dest);

    protected:
    private:
};



#endif // MAPMANAGER_H
