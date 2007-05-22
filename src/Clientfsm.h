#ifndef CLIENTFSM_H_
#define CLIENTFSM_H_

#include <SDL.h>
#include <SDL_net.h>

class Connection;		// Forward declarations.
class ConnectionData;
class Message;
class MessageIn;
class MessageOut;
class Logger;
class Server;
class Client;

#define KEEPALIVE_TIME		(1000)	/**< Time elapsed between two consecutive Keep Alive.*/
#define KEEPALIVE_TIMEOUT	(4000)		/**< Time to wait for KeepAlive from client.*/

enum client_fsm_trans {t_ack_time, t_login, t_login_ok, t_login_failed, t_ka_ack_sent,
						t_ka_received, t_ka_timeout, t_sck_down, t_disconnect};

/**
 * Finished states machine for the client.
 */
class ClientFSM {

	public:
	/**
	 * Builds a Client Finished state machine.
	 *
	 * @author dndvault
	 * @author stonedz
	 * @since pre-alpha
	 * @param data A ConnectionData pointer.
	 * @param server Pointer to the server I'm running in.
	 * @param client Pointer to the client I belong to.
	 */
	ClientFSM(ConnectionData *data, Server* server, Client* client);

	/**
	 * Starts the FSM.
	 *
	 * @author dndvault
	 * @author stonedz
	 * @since pre-alpha
	 */
	void Start(void);

	/**
	 * Evolve to the next state of the machine.
	 *
	 * @author dndvault
	 * @author stonedz
	 * @since pre-alpha
	 */
	void Evolve(void);

	/**
	 * Stops the FSM.
	 *
	 * @author dndvault
	 * @author stonedz
	 * @since pre-alpha
	 */
	void Stop(void);

	/**
	 * Returns true if the machine is running, false if
	 * the machine is stopped.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @return True if running, flse if stopped.
	 */
	bool getStatus(void);

protected:
	/**
	 * Executes translations between states
	 *
	 * @author dndvault
	 * @author stonedz
	 * @since pre-alpha
	 * @param t state to evelve to.
	 */
	bool ExecTrans(client_fsm_trans t);

	void (ClientFSM::*ExecState)(void);

	////////////////////////
	// Machine States START
	////////////////////////

	/**
	 * Sends an ack to the client after the reception of a
	 * keep alive message from the client.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 */
	void SendKA_ACK(void);

	/**
	 * Main Client loop.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @todo implements an extern interpreter to switch message types.
	 */
	void Ready(void);

	/**
	 * Logs an user.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @todo This method needs a real implementation.
	 * @todo Add CRC and SHA controls.
	 */
	void Login(void);

	/**
	 * Disconnects an user.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 */
	void Disconnect(void);

	/**
	 * Resets the time elapsed between two KA.
	 *
	 * @author dndvault
	 * @author stonedz
	 * @since pre-alpha
	 */
	void ResetKATime(void);

	////////////////////////
	// Machine States STOP
	////////////////////////



private:
	/**
	 * Authenticate an user from his MSG_LOGIN message. If the authentification
	 * is correctly finished an Account instance is created and attacched to the Client
	 * this Finished state machine is running in.
	 *
	 * @author dndvault
	 * @author stonedz
	 * @since pre-alpha
	 * @param msg Pointer to the MSG_LOGIN message
	 * @return True if ok, false elsewhere.
	 */
	bool authenticate(MessageIn *msg);

    /**
	 * Manages received chat messages.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @param message Pointer to the received message. No need do delete it.
	 * @todo Implements a real MSG_* handler!
	 */
    void chat(MessageIn* message);

    /**
     * Manages received MSG_MOVE messages.
     *
     * @author stonedz
     * @since pre-alpha
     * @param message Pointer to the received message. No need do delete it.
     * @todo Implements a real MSG_* handler!
     */
    void move(MessageIn* message);

private:

	bool endFSM; 			/**< Indicates if the FSM is working or if it is stopped. */
	ConnectionData * data;	/**< Useful connection's (Client) data. */
	SDLNet_SocketSet set; 	/**< Client's socket set. */
	unsigned char livePtr;	/**< Simulate a live prompt. */
	Uint32 lastKA;			/**< Time of last received KA. */
	Logger* logger;         /**< Logger instance (Singleton no need to free it). */
	Server* myServer;       /**< Points to the server. */
	Client* myClient;       /**< Points to the Client that is running this machine. */
};

#endif /*CLIENTFSM_H_*/
