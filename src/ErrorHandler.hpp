/* ErrorHandler.hpp
 */

#ifndef _ERRORHANDLER_H_
#define _ERRORHANDLER_H_

#include <iostream>

#include "SDL/SDL.h" // For SDL_GetError()

// Put in namespace?

class ErrorHandler
{
    public:
        /* This enum holds the type of errors I might wanna report, Fatal errors will have the program exit/quit/abort
         * while others can be handled accordingly.
         */
        enum ErrorType {
            FATAL_CONSTRUCTOR_ERROR = 0,
            NONFATAL_CONSTRUCTOR_ERROR,
            FATAL_ERROR,
            NONFATAL_ERROR
        };

        /* This function is the main error handling function, therefore being declared static so all can use it without
         * actually creating an ErrorHandler object. Internally it outputs the error to stderr and to a log file.
         */
        static void OutputError(ErrorType eType, std::string Error);
};

#endif
