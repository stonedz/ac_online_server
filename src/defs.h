#ifndef DEFS_H_
#define DEFS_H_

// General constants
#define SERVER_VERSION      "pre-alpha" /**< Server version. */
#define SERVER_MAIN_PORT    (9999)      /**< Network port the server is listening to. */

// Different types of messages that the console can print.
#define CONSOLE_INFO        (1)
#define CONSOLE_WARNING     (2)
#define CONSOLE_ERROR       (3)
#define CONSOLE_DEBUG       (4) /**< Debug messages. */

// Timers, in milliseconds.
#define KEEPALIVE_TIME		(1000)	/**< Time elapsed between two consecutive Keep Alive.*/
#define KEEPALIVE_TIMEOUT	(4000)	/**< Time to wait for KeepAlive from client.*/

// We define here our game refresh rate, in millisecodns
#define GAME_UPDATE         (100)                       /**< Milliseconds to wait for an update. you _MUST_ use a submultiple of 1000. */
#define GAME_UPDATES_SECOND (1000 / GAME_UPDATE)        /**< Updates for a real second. */
#define GAME_UPDATES_MIN    (60 * GAME_UPDATES_SECOND)  /**< Updates for a real minute. */
#define GAME_UPDATES_HOUR   (60 * GAME_UPDATES_MIN)     /**< Updates for a real hour. */
#define PERFLOG_SIZE_SHORT  (60)                        /**< Size soft-limit for the perfLogShort vector. (seconds)*/
#define PERFLOG_SIZE_MED    (30)                        /**< Size soft-limit for the perfLogLong vector. (minutes)*/
#define PERFLOG_SIZE_LONG   (48)                        /**< Size soft-limit for the perfLogHuge vector. (30 minutes)*/

// Objects types
#define GO_INVALID  (0)             /**< Invalid game object. */
#define GO_PLAYER   (1)             /**< A player. */

// Log modes
#define LOGMODE_NORMAL (1)	        /**< Log to the standard logfile. */
#define LOGMODE_ERROR (2)	        /**< Log to the error logfile. */
#define LOGMODE_AUTH (3)	        /**< Log to the auth logfile. */
#define LOGMODE_DB (4)              /**< Log to the database logfile. */

// Define the paths of previously defined log-modes.
#define LOGFILE_NORMAL  "log/log"
#define LOGFILE_ERROR   "log/error-log"
#define LOGFILE_AUTH    "log/auth-log"
#define LOGFILE_DB      "log/db-log"

// Network messages types
#define MSG_INVALID (0)		/**< Invalid message. */
#define MSG_LOGIN 	(1)		/**< Login message, a client wants to authenticate. */
#define MSG_LOGOUT 	(2)		/**< Logout message, a client wants to quit. */
#define MSG_CHAT 	(3)		/**< Chat message, a normal (generic)  chat message.*/
#define MSG_KA		(4)		/**< Keep Alive message (client send this message).*/
#define MSG_KA_ACK	(5)		/**< Keep Alive ACK (server reply to KA with this message).*/
#define MSG_MOVE	(6)		/**< Movement message: from client to server requests a destination, from server to client allow a movement. */

#define DB_ACCOUNTS     "accounts.db"   /**< Filename for the accounts database. */

#endif
