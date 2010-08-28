/* Logger.hpp
 *
 * Changelog:
 * 27/08/2010: - I no longer flush the clog/LogFile buffers after the logger test.
 * 24/08/2010: - Added internal functions for each, logging to cerr and to an ofstream.
 *             - Added support for logging to an ofstream.
 *             - Added a verbosity enum to support different levels of logging.
 *             - Changed LogFile's name to "log.txt" to show that it's not only errors :P
 *             - Removed the internal functions for outputting to clog/ofstream, it's not worth copying the std::string
 *               twice if it's 3 lines of code for both <_<
 *             - Redone the LogType and Verbosity enums, they're now completely seperate and an error/log can have any
 *               level of verbosity.
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
            CONSTRUCTOR = 0, // For anything that happens in a constructor, it's serious business!
            RUNTIME          // They're all technically runtime (:P) but this one is for any misc. runtime reporting.
                             // Probably should come up with a better name...
        };

        /* This enum holds the verbosity level of the logger. I might wanna keep it completely silent and not output a
         * single char or make it very verbose. Will definitely help in debugging later on. Since any error or info to
         * be logged/outputted/printed wil pass through here, keeping the level here is probably a good idea.
         *
         * They're just placeholder values for now, I'll implement the details later.
         */
        enum Verbosity {
            SILENT = 0, // Complete silence, no output at all.
            FATAL,      // Only report fatal errors, so in theory there should only be 1 error per run :P
            ERROR,      // Also include normal non fatal errors.
            INFO,       // Report a bit more info, mostly useful stuff like flags on startup, video driver etc.
            VERBOSE,    // Reports tons of stuff, not sure what to include yet.
            ZOMG        /* Reports EVERYTHING that I'll be making loggible. Again, not sure what to report but
                         * performance may become an issue at this level so I should come up with a better way of
                         * logging than copying the std::string over. */
        };

        /* This function is the main info reporting function, therefore being declared static so all can use it without
         * actually creating an ErrorHandler object. Internally it outputs the error to stderr and to a log file.
         *
         * Some statistics as per the 27/08/2010 version:
         *  12.13s: 1mil calls
         *  08.21s: 1mil calls, noflush
         *  00.18s: 1mil calls, verbosetest inside Log(), string created before call
         *  00.14s: 1mil calls, verbosetest inside Log(), string created at call
         *  00.00s: 1mil calls, verbosetest in main()
         */
        static void Log(LogType lType, Verbosity vLevel, std::string Info);

    private:
        static std::ofstream LogFile; // TODO?: Let the user pick the logfile's name.
        static int VerbosityLevel;
};

#endif
