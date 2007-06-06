#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <iosfwd>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "SDL.h"
#include "defs.h"

/**
 * A simple logging system, implements Singleton pattern. Threadsafe.
 *
 * @todo TODO Porting existing code in order to use logging system.
 */
class Logger
{
protected:
	/**
	 * Constructor.
	 */
	Logger();

	/**
	 * Virtual destructor.
	 */
	virtual ~Logger();

private:

	static Logger* pUniqueInstance;	/**< Logger instance. */
	static SDL_mutex* mxInstance;	/**< Instance mutex, for thread safetyness. */

public:
	/**
	 * Gets the logger instance. Since this class implements
	 * the Singleton pattern, this method is the one to be called
	 * to get an usable instance.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @return The Logger instance.
	 */
	static Logger* getInstance();

	/**
	 * Frees the Logger instance and its memory.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 */
	static void freeInstance();

	/**
	 * Sets or unsets the debug mode. Default behaviour of the Logger object
	 * is to start with debugMode off.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @param flag Sets or unsets debug mode.
	 */
	void setDebugMode(bool flag = true);

	/**
	 * Logs a message, adding a timestamp and possibly more informations.
	 *
	 * @author stonedz
	 * @since pre-alpha
	 * @param msg Constant reference to the message to log.
	 * @param mode Logging mode, For available modes please check Logger.h define.
	 */
	void log(const std::string &msg, Uint16 mode);

	/**
	 * Returns a pre-formatted string with localtime.
	 *
	 * @author sotnedz
	 * @since pre-alpha
	 * @return Current time.
	 */
	 std::string getCurrentTime();

private:
	/*
	 * @todo stonedz: I would like to use a stream's vector or a stream's map
	 * in order to be able to register as many logfiles as we want, even during
	 * runtime.
	 */
	std::ofstream LogFile;		/**< Standard log file.*/
	std::ofstream ErrLogFile;	/**< Error log file. */
	std::ofstream AuthLogFile;	/**< Authentication log file. */
	std::ofstream DBLogFile;    /**< Database log file. */

	SDL_mutex* mxStdLogger;     /**< Mutex for standard logfile. */
	SDL_mutex* mxErrLogger;     /**< Mutex for error logfile. */
	SDL_mutex* mxAuthLogger;    /**< Mutex for authentication logfile. */
    SDL_mutex* mxDBLogger;       /**< Mutex for the Database logfile. */

	SDL_mutex* mxLoggerProp;    /**< Mutex fo general Logger's properties. */

	/**
	 * When true, the output will be printed to the logfile AND to the standard
	 * output stream (the error log will be printed to the standard error stream).
	 *
	 * Deafult value is false.
	 */
	bool debugMode;
};

#endif /*LOGGER_H_*/
