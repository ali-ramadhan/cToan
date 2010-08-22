#include "ErrorHandler.hpp"

void
ErrorHandler::OutputError(ErrorType eType, std::string Error)
{
    std::string FullError = "Oh shit, there was an error. *facepalm*\n"; // The preamble part.
    switch (eType) {
        case FATAL_CONSTRUCTOR_ERROR:
            FullError += "SDL_GetError(): " + std::string(SDL_GetError()) + '\n';
            FullError += "DEBUG: " + Error; // The error I report is less important than SDL_GetError().
            FullError += "This error originated from a constructor, the program will abort by itself.\n";
            std::cout << FullError;
            break;

        case NONFATAL_CONSTRUCTOR_ERROR:
            break;

        case FATAL_ERROR:
            break;

        case NONFATAL_ERROR:
            break;

        default:
            ;
    }
}
