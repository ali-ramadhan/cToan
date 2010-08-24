#include "Logger.hpp"

void
Logger::Log(LogType lType, std::string Info)
{
    switch (eType) {
        case FATAL_CONSTRUCTOR_ERROR:
            std::string FullInfo = "Oh shit, there was a fatal constructor error. *facepalm*\n";
            FullInfo += "SDL_GetError(): " + std::string(SDL_GetError()) + '\n';
            FullInfo += "DEBUG: " + Error; // The error I report is less important than SDL_GetError().
            FullInfo += "This error originated from a constructor, the program will abort by itself.\n";
            std::cout << FullError;
            break;

        default:
            ;
    }

    OutputToStderr(FullInfo);
    OutputToFile(FullInfo);
}

void
Logger::OutputToStderr(std::string Info)
{
    std::cout << FullInfo << std::flush;
}

void
Logger::OutputToFile(std::string Info)
{
    if (!this->LogFile.is_open()) {
        LogFile.open("stderr.txt", std::ios::out | std::ios::app);
    }

    LogFile << Info.c_str();
    LogFile.flush();
}
