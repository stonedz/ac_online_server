#include "Gamefsm.h"
#include "Client.h"
#include "Account.h"
#include "Char.h"
#include "Logger.h"
#include "Server.h"
#include "Message.h"
#include "MessageOut.h"
#include <boost/lexical_cast.hpp>

#include <iostream>
#include <map>
#include <deque>

Gamefsm::Gamefsm(Server* server)
    :myLogger(Logger::getInstance()),
    exitRequest(false),
    exitLoop(false),
    myThread(NULL),
    myServer(server),
    loopCounter(0),
    logEnabled(false),
    perfLogShort(0),
    perfLogLong(0),
    perfLogMedium(0),
    updateTime(0),
    mxLogEnabled(SDL_CreateMutex()),
    mxPerfLogShort(SDL_CreateMutex()),
    mxPerfLogLong(SDL_CreateMutex()),
    mxPerfLogMedium(SDL_CreateMutex())

{
    #ifdef TESTPHASE
    setLog(true);   // enabling logging capabilies.
    #endif
}

Gamefsm::~Gamefsm()
{
    SDL_DestroyMutex(mxLogEnabled);
    SDL_DestroyMutex(mxPerfLogShort);
    SDL_DestroyMutex(mxPerfLogMedium);
    SDL_DestroyMutex(mxPerfLogLong);
}


void Gamefsm::threadBody(){
    ExecTrans(t_init);
    while(!exitLoop){
        Evolve();
        if(updateTime > GAME_UPDATE){ // Last update took more than GAME_UPDATE time!
            std::string toLog = "Last update took "+ boost::lexical_cast<std::string>(updateTime) +
                                " milliseconds to complete, GAME_UPDATE is set at " + boost::lexical_cast<std::string>(GAME_UPDATE)
                                + " milliseconds. Lower GAME_UPDATE or buy a faster machine!";
            myLogger->log(toLog,LOGMODE_NORMAL);
            myServer->getConsole().printMsg(toLog, CONSOLE_ERROR);
        }
        else{
            SDL_Delay(GAME_UPDATE - updateTime);
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
        loopCounter++; // We can run 13,5 years with an update of 100 milliseconds.
        std::cout.flush(); // Flush the standard out stream to prevent console lockups.

        if ((loopCounter % GAME_UPDATES_SECOND) == 0){ // Every second do...

            // Performance log
            if(logEnabled){
                #ifdef TESTPHASE
                perfLogShort.push_back(updateTime);             // Logs performances as the time needed for previous update.
                if (perfLogShort.size() > PERFLOG_SIZE_SHORT){  // If the queue is empty deletes the oldest record
                    perfLogShort.pop_front();
                    if((loopCounter % GAME_UPDATES_MIN) == 0){  // First minute is ignored here.
                        perfLogMedium.push_back(getPerformanceShort());
                        if (perfLogMedium.size() > PERFLOG_SIZE_MED){
                            perfLogMedium.pop_front();
                            if((loopCounter % (GAME_UPDATES_MIN * 30)) == 0){
                                perfLogLong.push_back(getPerformanceMedium());
                                if(perfLogLong.size() > PERFLOG_SIZE_LONG){
                                    perfLogLong.pop_front();
                                }
                            }
                        }
                    }
                }

                #endif
            }

            // Start movement
            std::map<Uint32, Client*>& rClients = myServer->getClients();
            Char* pAChar; //Tmp pointer to chars.
            Uint32 ax,ay,az;
            for(miClientsIterator = rClients.begin(); miClientsIterator != rClients.end(); miClientsIterator++){
                pAChar = (((miClientsIterator->second)->getAccount())->getChar());
                if(pAChar->move()){ // We moved! let's inform the client of its new position.
                    (pAChar->getPosition()).getXYZ(ax,ay,az);
                    //Create a new messageout and send it!
                    MessageOut* messageout;
                    messageout = new MessageOut(MSG_MOVE);
                    messageout->write2(12); //The lenght of a MSG_MOVE
                    messageout->write4(ax);
                    messageout->write4(ay);
                    messageout->write4(az);
                    messageout->addCRC();
                    Connection::putMessage((miClientsIterator->second)->getSocket() ,messageout);
                    delete messageout;


                    std::cout << ax << "," << ay << std::endl;
                }
            }
            // END movement
        } // END second update.
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

Uint16 Gamefsm::getPerformanceInst(){
    SDL_LockMutex(mxPerfLogShort);
    Uint16 tmp = perfLogShort.back();
    SDL_UnlockMutex(mxPerfLogShort);

    return (tmp * 100) / GAME_UPDATE; // Returns the percentage.

}

Uint16 Gamefsm::getPerformanceShort(){
    Uint16 tmp = 0;
    Uint16 size;
    if((size = perfLogShort.size())){
        for (Uint16 counter = 0; counter < size; counter++)
            tmp += perfLogShort[counter];

        return (((tmp / size) * 100) / GAME_UPDATE); // Calculates the average.
    }
    else
        return 0;
}

Uint16 Gamefsm::getPerformanceMedium(){
    Uint16 tmp = 0;
    Uint16 size;
    if((size = perfLogMedium.size())){
        for (Uint16 counter = 0; counter < size; counter++)
            tmp += perfLogMedium[counter];

        return (((tmp / size) * 100) / GAME_UPDATE); // Calculates the average.
    }
    else
        return 0;
}

Uint16 Gamefsm::getPerformanceLong(){
    Uint16 tmp = 0;
    Uint16 size;
    if((size = perfLogLong.size())){
        for (Uint16 counter = 0; counter < size; counter++)
            tmp += perfLogLong[counter];

        return (((tmp / size) * 100) / GAME_UPDATE); // Calculates the average.
    }
    else
        return 0;
}
