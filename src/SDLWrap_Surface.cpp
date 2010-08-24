#include "SDLWrap_Surface.hpp"
#include <iostream>
namespace SDLWrap {

Surface::Surface(const std::string FilePath)
try {
    SDL_Surface *tmpSurface = NULL;
    if ( (tmpSurface = SDL_LoadBMP(FilePath.c_str())) == NULL)
        throw SurfaceCreationError();

    if ( (this->me = SDL_DisplayFormat(tmpSurface)) == NULL )
        throw SurfaceCreationError();
    
    SDL_FreeSurface(tmpSurface);
}
catch (SurfaceCreationError)
{
    ErrorHandler::OutputError(ErrorHandler::FATAL_CONSTRUCTOR_ERROR, "Surface::Surface(char*) constructor threw a SurfaceCreationError.\n");
}

Surface::~Surface()
{
    SDL_FreeSurface(this->me);
}

bool
Surface::Blit(Surface * const Destination)
{
    return ( RealBlit(Destination, NULL, NULL) == 0 );
}

bool
Surface::Blit(Surface * const Destination, int DestXOffset, int DestYOffset)
{
    SDL_Rect OffsetRect;
    OffsetRect.x = DestXOffset;
    OffsetRect.y = DestYOffset;
    return ( RealBlit(Destination, NULL, &OffsetRect) == 0 );
}

bool
Surface::RealBlit(Surface * const Destination, SDL_Rect *SourceRect, SDL_Rect *DestRect)
{
    while ( SDL_BlitSurface(this->me, SourceRect, Destination->me, DestRect) == -2 ) {
        /* Reload the image and reblit. Too lazy to implement now but the SDL docs have something on it and so does a
         * very good post by rip-off on GameDev.
         * http://sdl.beuc.net/sdl.wiki/SDL_BlitSurface
         * http://www.gamedev.net/community/forums/topic.asp?topic_id=518486&whichpage=1&#3368336
         */
        continue;
    }

    return true;
}

};
