#ifndef CLIENT_H_
#define CLIENT_H_

#include "SDL.h"
#include "SDL_net.h"
#include "SDL_thread.h"

#include "Connection.h"

class Server; 	// Forward declarations
class Clientfsm;
class Account;

/**
 * Represents a client.
 *
 * Waits for messages from a client and manage it.
 */
class Client : public Connection
{
public:

	/**
	 * Constructs a Client.
	 *
	 * It bascally creates a ConnectionData instance and fills it with
	 * Client's data, then it creates a new thread to run in.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @param socket The TCP socket created by the server.
	 * @param server The server in which the client will run.
	 */
	Client(TCPsocket socket, Server* server);

	/**
	 * Virtual destructor.
	 */
	virtual ~Client();

	/**
	 * Listening routine. Manages the reception of messages from remote host.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @param data Contains the client's data that was initialized in Client's constructor.
	 * @todo TODO Check if the way we free resources is correct.
	 * @todo TODO Improve error handling.
	 */
	void startListen(ConnectionData * data);

    /**
     * Attach an account instance to the Client.
     *
     * @author stonedz
     * @since pre-alpha
     * @param account An Account pointer.
     */
	void setAccount(Account* account);

	/**
	 * Returns a pointer to the Client's account.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @return A pointer to the current Client's account.
	 */
	Account* getAccount() {return myAccount;}

	/**
	 * Returns a reference to the server the client is running in.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 */
	Server& getServer();

private:

	Server* myServer; 	/**< Points to the server I'm running in.*/
	Account* myAccount; /**< Points to Client's account. */
};

#endif /*CLIENT_H_*/
