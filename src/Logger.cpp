#include "Logger.hpp"

std::ofstream Logger::LogFile("log.txt", std::ios::out | std::ios::app);
int           Logger::VerbosityLevel = Logger::ZOMG; // For now.

void
Logger::Log(LogType lType, Verbosity vLevel, std::string Info)
{
    // If the verbosity level of the error is higher than what we want to report, return now.
    if (vLevel >= Verbosity)
        return;

    std::string FullInfo("");
    switch (lType) {
        case CONSTRUCTOR:
            switch (vLevel) {
                case FATAL:
                    FullInfo += "Oh shit, there was a fatal constructor error. *facepalm*\n";
                    FullInfo += "SDL_GetError(): " + std::string(SDL_GetError()) + '\n';
                    FullInfo += "FATAL: " + Info; // The error I report is less important than SDL_GetError().
                    FullInfo += "This error originated from a constructor, the program will abort by itself.\n";
                    break;
            }
            break;

        case RUNTIME:
            switch (vLevel) {
                case ERROR:
                    FullInfo += "ERROR: " + Info;
                    break;
            }
            break;

        default:
            ;
            break;
    }

    /* The buffers used to be flushed but are not so anymore. Each time I flush, especially the LogFile, it has to save
     * the data to the disk which takes quite a lot of time. Plus, it'll all end up in the file anyways, why worry.
     */
    std::clog << FullInfo;
    LogFile << FullInfo.c_str();
}
