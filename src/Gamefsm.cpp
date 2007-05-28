#include "Gamefsm.h"
#include "Logger.h"
#include "Server.h"
#include <boost/lexical_cast.hpp>

#include <iostream>

Gamefsm::Gamefsm(Server* server)
    :myLogger(Logger::getInstance()),
    exitRequest(false),
    exitLoop(false),
    myThread(NULL),
    myServer(server),
    loopCounter(0),
    logEnabled(false),
    perfLogShort(),
    perfLogLong(),
    mxLogEnabled(SDL_CreateMutex()),
    mxPerfLogShort(SDL_CreateMutex()),
    mxPerfLogLong(SDL_CreateMutex())

{
    // This should enhanche performances for std::vector dynamic memory allocation.
    perfLogShort.reserve(PERFLOG_SIZE_SHORT);
    perfLogLong.reserve(PERFLOG_SIZE_LONG);
    #ifdef TESTPHASE
    setLog(true);   // enabling logging capabilies.
    #endif
}

Gamefsm::~Gamefsm()
{
    SDL_DestroyMutex(mxLogEnabled);
    SDL_DestroyMutex(mxPerfLogShort);
    SDL_DestroyMutex(mxPerfLogLong);
}


void Gamefsm::threadBody(){
    ExecTrans(t_init);
    while(!exitLoop){
        Evolve();
        if(updateTime > GAME_UPDATE){ // Last update took more than GAME_UPDATE time!
            std::string toLog = "Last update took "+ boost::lexical_cast<std::string>(updateTime) +
                                " to complete, GAME_UPDATE is set at " + boost::lexical_cast<std::string>(GAME_UPDATE)
                                + " milliseconds. Lower GAME_UPDATE or buy a faster machine!";
            myLogger->log(toLog,LOGMODE_NORMAL);
            std::cerr << toLog << std::endl;
        }
        else{
            SDL_Delay(GAME_UPDATE - updateTime);
            //if ((loopCounter+1) == GAME_LOOPS){
            //    std::cout << SDL_GetTicks() << "*" << updateTime << std::endl;
            //}

        }

    }

}

void Gamefsm::Start(){
    myThread = SDL_CreateThread(startThread, this); // Starts the thread
    if (myThread == NULL){ // Something went terribly wrong :D
        std::string toLog;
        toLog = "Unable to create Gamefsm Thread :";
        toLog.append(SDL_GetError());
        myLogger->log(toLog, LOGMODE_ERROR);
        exit(5);
    }
}

void Gamefsm::Stop(){
    exitRequest = true;
}

void Gamefsm::Evolve(){
    (this->*ExecState)();
}


SDL_Thread* Gamefsm::getThread(){
    return myThread;
}

bool Gamefsm::ExecTrans(game_fsm_trans t){
    switch(t){
        case t_init: // initializes the game.
            ExecState = &Gamefsm::Init;
            break;
        case t_main: // Main loop , updates the game.
            ExecState = &Gamefsm::Update;
            break;
        case t_quit: //Quits the game, save and prepare for a clean shutdown.
            ExecState = &Gamefsm::Quit;
            break;
        default:
            myLogger->log("Unsupported transition in ClientFSM",LOGMODE_ERROR);
    }
    return true;
}

void Gamefsm::Init(){
    // Initialize the game...then when ok
    myServer->setInit(true);
    // then pass the control to the main loop.
    ExecTrans(t_main);
}

void Gamefsm::Update(){
    beginUpdate = SDL_GetTicks(); // we begin the update process and we have to know how much time we spend on it.
    if(exitRequest){
        ExecTrans(t_quit);
    }
    else{ // Main update loop
        loopCounter = (loopCounter+1) % GAME_LOOPS; // Updates the loopCounter, it will be reset when GAME_LOOPS limit is reached.
        // Dummy loop to test updateTime behaviour
        if ((loopCounter+1) == GAME_LOOPS){ // a game loop.

            // LOG
            if(logEnabled){
                #ifdef TESTPHASE
                perfLogShort.push_back(updateTime); // Logs performances as the time needed for previous update.

                // TODO this should be done by the upcoming Garbage Collector (#3)
                if(perfLogShort.size() > PERFLOG_SIZE_SHORT){
                    Uint16 count = 1;
                    while(count <= PERFLOG_SIZE_SHORT){
                        perfLogLong.push_back(perfLogShort[count]); // Logs samples from the perfLogShort vector for long performances computation.
                        count +=  (PERFLOG_SIZE_SHORT / 50);
                    }
                    perfLogShort.clear();                       // erase vector's content.
                }
                #endif
            }

        }
        #ifdef TESTPHASE
        Uint32 af;
        for (Uint32 c =0; c< 1000000; c++)
            af = c;
        #endif
    }
    updateTime = SDL_GetTicks() - beginUpdate;
}

void Gamefsm::Quit(){
    // Save the game and prepare for a proper shutdown
    //std::cout << std::endl << "quitting GAMEFSM";
    exitLoop = true;
}

int Gamefsm::startThread(void * data){
    Gamefsm* instance = reinterpret_cast<Gamefsm *>(data);
    instance->threadBody(); // Pass the control to the threadBody.
    return 1;
}

void Gamefsm::setLog(bool set){
    SDL_LockMutex(mxLogEnabled);    // Locks the mutex...
    logEnabled = set;               // ...sets the var...
    SDL_UnlockMutex(mxLogEnabled);  // ...unlocks the mutex.
}
