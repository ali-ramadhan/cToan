#include "SDLWrap_Display.hpp"

namespace SDLWrap {

Display::Display(int Width, int Height, int BPP, Uint32 Flags)
try {
    if ( (this->me = SDL_SetVideoMode(Width, Height, BPP, Flags)) == NULL)
        throw SurfaceCreationError();
}
catch(SurfaceCreationError)
{
   ErrorHandler::OutputError(ErrorHandler::FATAL_CONSTRUCTOR_ERROR, "Display::Display(int, int, int, Uint32) constructor threw a SurfaceCreationError!\n");
}

bool
Display::Flip()
{
    return (SDL_Flip(this->me) == 0);
}

}
