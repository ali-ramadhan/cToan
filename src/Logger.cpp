#include "Logger.hpp"

std::ofstream Logger::LogFile("log.txt", std::ios::out | std::ios::app);

void
Logger::Log(LogType lType, std::string Info)
{
    // Do a comparision to see if the info to be logged is more verbose than asked for, if so, then return now.

    std::string FullInfo("");
    switch (lType) {
        case FATAL_CONSTRUCTOR_ERROR:
            FullInfo += "Oh shit, there was a fatal constructor error. *facepalm*\n";
            FullInfo += "SDL_GetError(): " + std::string(SDL_GetError()) + '\n';
            FullInfo += "INFO: " + Info; // The error I report is less important than SDL_GetError().
            FullInfo += "This error originated from a constructor, the program will abort by itself.\n";
            break;

        default:
            ;
            break;
    }

    std::clog << FullInfo << std::flush;
    LogFile << FullInfo.c_str();
    LogFile.flush();
}
