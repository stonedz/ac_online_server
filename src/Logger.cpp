#include "Logger.h"
#include <time.h>

Logger* Logger::pUniqueInstance = NULL; // Reference to the unique instance.
SDL_mutex* Logger::mxInstance = SDL_CreateMutex();	// Reference to instance mutex.

Logger* Logger::getInstance(){
	SDL_LockMutex(mxInstance);	// Locks the mutex...
	if (pUniqueInstance == NULL){ // No instance, create one.
		pUniqueInstance = new Logger;
	}
	SDL_UnlockMutex(mxInstance);	// Locks the mutex...
	return pUniqueInstance;
}

void Logger::freeInstance(){
	SDL_LockMutex(mxInstance);	// Locks the mutex...
	if (pUniqueInstance != NULL) {
		delete pUniqueInstance;
		pUniqueInstance = NULL;
	}
	SDL_LockMutex(mxInstance);	// Locks the mutex...
}

Logger::Logger()
	:LogFile(LOGFILE_NORMAL, std::ios::trunc),
	ErrLogFile(LOGFILE_ERROR, std::ios::app),
	AuthLogFile(LOGFILE_AUTH, std::ios::app),
	DBLogFile(LOGFILE_DB, std::ios::app),
	mxStdLogger(SDL_CreateMutex()),
	mxErrLogger(SDL_CreateMutex()),
	mxAuthLogger(SDL_CreateMutex()),
	mxDBLogger(SDL_CreateMutex()),
	mxLoggerProp(SDL_CreateMutex()),
	debugMode(false)
{
}

Logger::~Logger()
{
// std::ofstream destructors take care of closing file descriptors
	SDL_DestroyMutex(mxStdLogger);
	SDL_DestroyMutex(mxErrLogger);
	SDL_DestroyMutex(mxAuthLogger);
	SDL_DestroyMutex(mxDBLogger);
	SDL_DestroyMutex(mxLoggerProp);
}

std::string Logger::getCurrentTime(){
	struct tm  timeinfo;
	time_t rawtime;

	time(&rawtime);
	timeinfo = *(localtime(&rawtime));

	std::ostringstream os;
	os  << std::setw(2) << std::setfill('0') << timeinfo.tm_mday
		<< "-" << std::setw(2) << std::setfill('0') << (timeinfo.tm_mon)+1
		<< " "
		<< "[" << std::setw(2) << std::setfill('0') << timeinfo.tm_hour
		<< ":" << std::setw(2) << std::setfill('0') << timeinfo.tm_min
		<< ":" << std::setw(2) << std::setfill('0') << timeinfo.tm_sec
		<< "] ";

	return os.str();
}

void Logger::setDebugMode(bool flag){
	// Locks the mutex...
	SDL_LockMutex(this->mxLoggerProp);	// Locks the mutex...
	this->debugMode = flag;
	SDL_UnlockMutex(this->mxLoggerProp);// ...unlocks the mutex
}

void Logger::log(const std::string &msg, Uint16 mode){
	if(mode == LOGMODE_NORMAL && this->LogFile.is_open()){// Normal log.
		SDL_LockMutex(this->mxStdLogger);
		this->LogFile << getCurrentTime() << msg << std::endl;

		if(this->debugMode){
			std::cout << "<Log> " << msg << std::endl;
		}

		SDL_UnlockMutex(this->mxStdLogger);
	}
	else if(mode == LOGMODE_ERROR && this->ErrLogFile.is_open()) {// Log a server error.
		SDL_LockMutex(this->mxErrLogger);
		this->ErrLogFile << getCurrentTime() << msg << std::endl;

		if(this->debugMode){
			std::cerr << "<ERR Log> " << msg << std::endl;
		}

		SDL_UnlockMutex(this->mxErrLogger);
	}
	else if(mode == LOGMODE_AUTH && this->AuthLogFile.is_open()){// Log an authentication or an authentication attempt.
		SDL_LockMutex(this->mxAuthLogger);
		this->AuthLogFile << getCurrentTime() << msg << std::endl;

		if(this->debugMode){
			std::cout << "<Auth Log> " << msg << std::endl;
		}

		SDL_UnlockMutex(this->mxAuthLogger);
	}
	else if(mode == LOGMODE_DB && this->DBLogFile.is_open()){// Log a database-related information or problem.
        SDL_LockMutex(this->mxDBLogger);
		this->DBLogFile << getCurrentTime() << msg << std::endl;

		if(this->debugMode){
			std::cout << "<DB Log> " << msg << std::endl;
		}

		SDL_UnlockMutex(this->mxDBLogger);
	}

}
