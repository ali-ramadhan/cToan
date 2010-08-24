#include "SDLWrap_SDLEngine.hpp"

namespace SDLWrap {

SDLEngine::SDLEngine(Uint32 InitFlags)
try {
    if (SDL_Init(InitFlags) != 0)
        throw InitError();
}
catch (InitError)
{
    Logger::Log(Logger::FATAL_CONSTRUCTOR_ERROR, "SDLEngine::SDLEngine(Uint32) constructor threw an InitError.\n");
}

SDLEngine::~SDLEngine()
{
    SDL_Quit();
}

Uint32
SDLEngine::WasInit(Uint32 Flags)
{
    return SDL_WasInit(Flags);
}

}
