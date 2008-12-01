#ifndef SERVER_H_
#define SERVER_H_

#include <map>

#include "SDL.h"

#include "Connection.h"
#include "MapManager.h"
#include "Gamefsm.h"
#include "Console.h"
#include "IDServer.h"

class Message;	// Forward declarations.
class MessageIn;
class MessageOut;
class Client;
class IDServer;

/**
 * Represents a server.
 *
 * Waits for new connections at given port and manages the creation
 * of new Clients. It also manages the creation of every other object needed by the server itself.
 */
class Server : public Connection
{
public:

	/**
	 * Constructs a Server.
	 *
	 * Initializes a server by creating a socket, filling a ConnectionData
	 * with server's informations and finally by creating a thread to run in.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @param port Port to run the server at.
	 * @todo Check exit codes and change them to exceptions.
	 */
	Server(int port);

	/**
	 * Virtual destructor
	 */
	virtual ~Server();

	/**
	 * Listening routine.
	 *
	 * A thread created previously during object's creation, will pass the control to this
	 * method. Here we listen for incoming connections, when activity
	 * is detected, we create a new Client, and it will automatically create
	 * a new thread to run in.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @param data Contains the server's data that was initialized in Server's constructor.
	 */
	void startListen(ConnectionData * data);

	/**
	 * Adds a Client to the clients' map. Thread-safe.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @param newClient Client to be added.
	 * @return True if ok, false elsewhere.
	 */
	bool addClient(Client* newClient);

	/**
	 * Deletes then removes a client from the clients' map. Thread-safe.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @param oldClient Client to be removed.
	 * @return True if ok, false elsewhere.
	 */
	bool removeClient(Client* oldClient);

	/**
	 * Gently request the server to quit.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @todo Check if a basic syncro is needed.
	 */
	void requestExit();

	/**
	 * Sets the server in chat mode. This means that its console will print all
	 * MSG_CHAT messages that clients send to the server.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @param value True to set the chat_mode, false to unset it.
	 */
	void setChatMode(bool value = true);

    /**
     * Sends a chat message to all the connected clients except the one that first
     * sent the message. If the server's console set the chat_mode it will display the chat
     * message to the console as well.
     *
     * @author stonedz
     * @since pre-alpha
     * @param sender Pointer to the Client that sent the chat message (it used in mClients map as a key), if 0 is the Server.
     * @param msg The chat message itself.
     * @todo Finish the implementation.
     */
	void generalChatMsg(Uint32 sender, std::string msg);

    /**
     * Returns next game object serial.
     *
     * @author stonedz
     * @since pre-alpha
     * @param validSerial Reference to an integer value to store the serial in. \
     * @see IGameObject
	 * @deprecated getNewID
     */
    void getNextGoSerial(Uint32& validSerial);
	
	/**
	 * Return a NEW game object serial.
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @param id The var where the new ID will be stored.
	 * @param type the Game Object type, see defines in defs.h files.
	 * @see defs.h
	 */
	void getNewID(Uint64& id, const Uint8& type);
	
	/**
	 * Updates the Server ID
	 * 
	 * @author stonedz
	 * @since pre-alpha
	 * @see IDServer
	 */
	Uint32 updateIDServer();

    /**
     * Sets the initialized var. It is used by Gamefsm.
     *
     * @author stonedz
     * @since pre-alpha
     * @param value
     */
    void setInit(bool value = true);

    /**
     * Returns a pointer to the server's map manager.
     *
     * @author stonedz
     * @since pre-alpha
     * @return Pointer to the server's map manager.
     */
    MapManager* getMapManager() {return myMapManager;}

    /**
     * Returns a reference to client's map.
     *
     * @author stonedz
     * @since pre-alpha
     * @return reference to mClients srd::map
     * @see mClients
     * @todo Maybe return a copy in order to avoid problems with syncronization and data corruptrion.
     */
    std::map<Uint32, Client*>& getClients() {return mClients;}

    /**
     * Returns a reference to the gamefsm the server is currently running.
     *
     * @author stonedz
     * @since pre-alpha
     * @return Reference to myGamefsm
     */
    Gamefsm& getGamefsm() {return myGamefsm;}

    /**
     * Returns a reference to the server's Console
     *
     * @author stonedz
     * @since pre-alpha
     * @return Reference to myConsole.
     */
    Console& getConsole() {return myConsole;}

private:

	/**
	 * Map containing active connections.
	 *
	 * The key is an unsigned, 32 bits long, integer, obtained
	 * by transforming an address of the Client's pointer into
	 * an integer. This will let us retrieve Clients easily.
	 */
	std::map<Uint32, Client*> mClients;

	SDL_mutex* mxClients;       /**< Mutex to avoid problems when dealing with the mClients map.*/
	MapManager* myMapManager;    /**< Pointer to a MapManager object which manages the game map (nothing to do with mClients). */
	bool exit_request;          /**< Proper exit request has benn submitted.*/
	bool chat_mode;             /**< This server's console will act like chat client, mainly for testing MSG_CHAT implementation. */
	SDL_mutex* mxGoSerial;      /**< Mutex for gameObjectSerial. */
	IDServer* myIdServer;    /**< The current Serial counter for game Objects (IGameObjects derived). */
	bool initialized;           /**< If true the server has been initialized, and may accept incoming connections. */
	Gamefsm myGamefsm;          /**< The Gamefsm that is running inside the Server. */
	Console myConsole;          /**< A console to control the server. */
};

#endif /*SERVER_H_*/
