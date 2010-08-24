/* Logger.hpp
 *
 * Changelog:
 * 24/08/2010: - Added internal functions for each, logging to cerr and to an ofstream.
 *             - Added support for logging to an ofstream.
 *             - Added a verbosity enum to support different levels of logging.
 *             - Changed LogFile's name to "log.txt" to show that it's not only errors :P
 *             - Removed the internal functions for outputting to clog/ofstream, it's not worth copying the std::string
 *               twice if it's 3 lines of code for both <_<
 */

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <iostream>
#include <fstream>

#include <SDL/SDL.h> // For SDL_GetError()

class Logger
{
    public:
        /* This enum holds the type of errors or info I might wanna report. Each can be handled accordingly, like I
         * might wanna call exit() upon reporting some FATAL error. Different types will be added as I need them.
         */
        enum LogType {
            FATAL_CONSTRUCTOR_ERROR = 0
        };

        /* This enum holds the verbosity level of the logger. I might wanna keep it completely silent and not output a
         * single char or make it very verbose. Will definitely help in debugging later on. Since any error or info to
         * be logged/outputted/printed wil pass through here, keeping the level here is probably a good idea.
         *
         * They're just placeholder values for now, I'll implement the details later.
         */
        enum Verbosity {
            SILENT = 0,
            FATAL,
            NORMAL,
            INFO,
            ZOMG
        };

        /* This function is the main error handling function, therefore being declared static so all can use it without
         * actually creating an ErrorHandler object. Internally it outputs the error to stderr and to a log file.
         */
        static void Log(LogType lType, std::string Info);

    private:
        static std::ofstream LogFile; // TODO?: Let the user pick the logfile's name.
};

#endif
