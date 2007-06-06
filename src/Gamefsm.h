#ifndef GAMEFSM_H
#define GAMEFSM_H

#include "SDL/SDL.h"
#include <deque>
#include <map>
#include "defs.h" // Constant definitions are defined here.

class Logger; // Forward declarations.
class Server;
class Client;

enum game_fsm_trans {t_main, t_quit, t_init};

/**
 * Manages the game with a finite state machine.
 *
 * This FSM runs in its own thread and manages the phases of the game. Non thread-safe,
 * (Only the Server instance will use it).
 */
class Gamefsm
{
public:
    /**
     * Constructor.
     */
    Gamefsm(Server* server);

    /**
     * Virtual destructor.
     */
    virtual ~Gamefsm();

    /**
     * Gamefsm body, it is where the FSM is started and controlled.
     *
     * @author stonedz
     * @since pre-alpha
     * @see startThread
     * @todo TODO Implements the anti-lag timing.
     */
    void threadBody();

    /**
     * Effectively starts the thread and FSM.
     *
     * @author stonedz
     * @since pre-alpha
     */
    void Start();

    /**
     * Stops the FSM.
     *
     * @author stonedz
     * @since pre-alpha
     */
    void Stop();

    /**
     * Evolve to the next state of the machine.
     *
     * @author stonedz
     * @since pre-alpha
     */
    void Evolve();

    /**
     * Returns the thread the Gamefsm is running into.
     *
     * @author stonedz
     * @since pre-alpha
     * @return A pointer to the thread the Gamefsm is running into.
     */
    SDL_Thread* getThread();

    /**
     * Sets the GameFSM logging capabilities,
     *
     * If set to true the all the logging capabilities of the GameFSM are turned on.
     * As for now they are:<ul><li>Performance logging.</li></ul>
     *
     * @author stonedz
     * @since pre-alpha
     * @param set the state we want to set the logging capability.
     */
    void setLog(bool set = true);

    /**
     * Returns a reference to the std::vector which contains collected short-term
     * performance data.
     *
     * @author stonedz
     * @since pre-alpha
     * @return Reference to perfLogShort
     */
    std::deque<Uint16>& getPerfLogShort() {SDL_LockMutex(mxPerfLogShort);
                                                return perfLogShort;
                                                SDL_UnlockMutex(mxPerfLogShort);}

    /**
     * Returns a reference to the std::vector which contains collected long-term
     * performance data.
     *
     * @author stonedz
     * @since pre-alpha
     * @return Reference to perfLogLong
     */
    std::deque<Uint16>& getPerfLogLong() {SDL_LockMutex(mxPerfLogLong);
                                                return perfLogLong;
                                                SDL_UnlockMutex(mxPerfLogLong);}

    /**
     * Returns a reference to the std::deque which contains collected mid-term
     * performance data.
     *
     * @author stonedz
     * @since pre-alpha
     * @return Reference to perfLogLong
     */
    std::deque<Uint16>& getPerfLogMedium() {SDL_LockMutex(mxPerfLogMedium);
                                                return perfLogMedium;
                                                SDL_UnlockMutex(mxPerfLogMedium);}

    /**
     * Returns Instant performance.
     *
     * @author stonedz
     * @since pre-alpha
     * @return Instant percentage of use of the server.
     */
    Uint16 getPerformanceInst();

    /**
     * Computes average perfomrance in the short-term period.
     *
     * The amount of time is PERFLOG_SIZE_SHORT seconds.
     *
     * @author stonedz
     * @since pre-alpha
     * @return Percentage of use of the server in the short-term period.
     */
    Uint16 getPerformanceShort();

    /**
     * Computes average performance in the mid-term period.
     *
     * The amount of time is PERFLOG_SIZE_MED minutes.
     *
     * @author stonedz
     * @since pre-alpha
     * @return Percentage of use of the server in the medium-term period.
     */
    Uint16 getPerformanceMedium();

    /**
     * Computes average performance in the very-long-term period.
     *
     * The amount of time is (PERFLOG_SIZE_LONG * 30) minutes.
     *
     * @author stonedz
     * @since pre-alpha
     * @return Percentage of use of the server in the long-term period.
     */
    Uint16 getPerformanceLong();

protected:


    /**
	 * Executes translations between states
	 *
	 * @author dndvault
	 * @author stonedz
	 * @since pre-alpha
	 * @param t state to evelve to.
	 */
	bool ExecTrans(game_fsm_trans t);

    void (Gamefsm::*ExecState)(void); /**< Pointer to the next machine state. */

    /////////////////////////
    // MACHINE STATES START
    /////////////////////////

    /**
     * Initializes the game, loads world, maps and everything
     * that is needed to activate the game.
     *
     * @author stonedz
     * @since pre-alpha
     */
    void Init();

    /**
     * Main loop, update the world.
     *
     * @author stonedz
     * @since pre-alpha
     */
    void Update();

    /**
     * Quits the game, save and prepare for a clean shutdown of the server.
     *
     * @author stonedz
     * @since pre-alpha
     */
    void Quit();

    /////////////////////////
    // MACHINE STATES STOP
    /////////////////////////

private:
    Logger* myLogger;                   /**< A Logger instance, no need to free it (Singleton). */
    bool exitRequest;                   /**< A polite exit request has been sent to the FSM. */
    bool exitLoop;                      /**< If true the FSM has exited and the whole loop may terminate. */
    SDL_Thread* myThread;               /**< The thread I'm running in (used to JOIN). */
    Server* myServer;                   /**< Pointer to the Server instance that created the Gamefsm. */
    Uint32 loopCounter;                 /**< Counts the game's cycles. */
    bool logEnabled;                    /**< If true enables performance data collection. */
    std::deque<Uint16> perfLogShort;    /**< If logEnabled is true, logs performances data (short term) at every loop (not every update!). Thread-safe access should be provided. */
    std::deque<Uint16> perfLogLong;     /**< If logEnabled is true, logs performances data (long term) at every loop (not every update!). Thread-safe access should be provided. */
    std::deque<Uint16> perfLogMedium;   /**< If logEnabled is true, logs performances data (medium term). */
    Uint16 updateTime;                  /**< Duration (in milliseconds) of the last Update() operation. */
    Uint32 beginUpdate;                 /**< Ticks (milliseconds) at the beginning of the Update() operation, used to calculate updateTime. */
    SDL_mutex* mxLogEnabled;            /**< Mutex for the access to the logEnabled var. */
    SDL_mutex* mxPerfLogShort;          /**< Mutex for the access to the perfLogShort var. */
    SDL_mutex* mxPerfLogLong;           /**< Mutex for the access to the perfLogLong var. */
    SDL_mutex* mxPerfLogMedium;         /**< Mutex for the access to the perrfLogMedium var. */
    std::map<Uint32, Client*>::iterator miClientsIterator; /**< Iterator for scanning the clients map. */


    /**
     * Wrapper around SDL threads, it simply callbacks threadBody method.
     *
     * This method is static cause it must be called as a pure C function by
     * SDL_CreateThread().
     *
     * @author stonedz
     * @since pre-alpha
     * @param data Pointer to self, used to call threadBody.
     * @return 1
     * @see threadBody
     */
    static int startThread (void * data);

};



#endif // GAMEFSM_H
