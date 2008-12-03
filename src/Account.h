#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <iostream>
#include "SDL.h"

class Char; // Forward declarations.
class Server;
class Client;

/**
 * Represents an account.
 */
class Account {
public:
    /**
     * Creates an account instance given its database id. This is what is used
     * when a Client successfully authenticate itself.
     *
     * @author stonedz
     * @since pre-aplha
     * @param id The id taken from the database.
     * @param username The account's username, retrieved from database.
     * @param name Real name, retrieved from the database.
     * @param surname Real surname, retrieved from the database.
     * @param email Vali email address, retrieved from database.
     */
    Account(Server* server,
            Client* client,
            Uint32 id,
            const std::string& username ,
            const std::string& name ,
            const std::string& surname ,
            const std::string& email,
            Uint32 char_id );

    /**
     * Virtual destructor.
     */
    virtual ~Account();

    /**
     * Returns Account's id
     *
     * @author stonedz
     * @since pre-alpha
     * @return A valid Account id.
     */
    Uint32 getId() {return myId;}

    /**
     * Returns a pointer to my character.
     *
     * @author stonedz
     * @since pre-alpha
     * @return a valid Char pointer.
     */
    Char* getChar() {return myChar;}

    /**
     * Begins the save process.
     *
     * @author stonedz
     * @since pre-alpha
     */
    void save();

private:
    Server* myServer;       /**< The server I'm running in. */
    Client* myClient;       /**< The client to which I belong. */
    Uint32 myId;            /**< Unique Account Id. */
    std::string myUsername; /**< Account's usernsme. */
    std::string myName;     /**< Real name. */
    std::string mySurname;  /**< Real surname. */
    std::string myEmail;    /**< Valid email. */
    Uint32 myCharID;        /**< Id of the account's character. */

    Char* myChar;           /**< My (active) character. */
	
	/**
	 * Returns character's gid taken from database.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @return 
	 */
	Uint64 loadGid(Uint32 db_id);


};

#endif /*ACCOUNT_H_*/
