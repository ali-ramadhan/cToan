#include "SDLWrap_SDLEngine.hpp"

namespace SDLWrap {

SDLEngine::SDLEngine()
{
    CoreWasInitialized = false;
    AlreadyShutdown    = false;
}

SDLEngine::SDLEngine(Uint32 InitFlags) throw(InitError)
try {
    if (SDL_Init(InitFlags) != 0) {
        throw InitError();
    } else {
        CoreWasInitialized = true;
    }

    AlreadyShutdown = false;

    Flags = WasInit(0);
}
catch (InitError)
{
    ErrorHandler::OutputError(ErrorHandler::FATAL_CONSTRUCTOR_ERROR, "SDLEngine::SDLEngine(Uint32) constructor threw an InitError.\n");
}

SDLEngine::~SDLEngine()
{
    if (!AlreadyShutdown) {
        Quit();
    }

    AlreadyShutdown = true;
}

void
SDLEngine::Init(Uint32 InitFlags) throw(InitError)
try {
    if (CoreWasInitialized) {
        return;
    }

    if (SDL_Init(InitFlags) != 0) {
        throw InitError();
    } else {
        CoreWasInitialized = true;
    }

    Flags = WasInit(0);
}
catch (InitError)
{
    ErrorHandler::OutputError(ErrorHandler::FATAL_CONSTRUCTOR_ERROR, "SDLEngine::Init(Uint32) threw an InitError.\n");
}

void
SDLEngine::InitSubSystem(Uint32 InitFlags) throw(InitError)
try {
    if (SDL_InitSubSystem(InitFlags) != 0) {
        throw InitError();
    }

    Flags = WasInit(0);
}
catch (InitError)
{   
    ErrorHandler::OutputError(ErrorHandler::FATAL_CONSTRUCTOR_ERROR, "SDLEngine::InitSubSystem threw an InitError.\n");
}

void
SDLEngine::Quit()
{
    if (AlreadyShutdown) {
        return;
    }

    SDL_Quit();
    AlreadyShutdown = true;
}

void
SDLEngine::QuitSubSystem(Uint32 QuitFlags)
{
    SDL_QuitSubSystem(QuitFlags);

    Flags = WasInit(0);
}

Uint32
SDLEngine::WasInit(Uint32 Flags)
{
    return SDL_WasInit(Flags);
}

}; // end namespace SDLWrap
