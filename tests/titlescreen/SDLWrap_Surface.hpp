#ifndef _SDLWRAP_SURFACE_H_
#define _SDLWRAP_SURFACE_H_

#include <string>

#include "SDL/SDL.h"

#include "ErrorHandler.hpp"

namespace SDLWrap {

/* This class acts as a wrapper around the SDL_Surface structure and defines the functions you would normally use with
 * SDL_Surfaces such as SDL_BlitSurface() and also provides useful shortcuts like a constructor that takes a BMP file
 * path.
 */
class Surface
{
    public:
        /* When caught it creates an error std::string which it sends to the Error Handler with the
         * FATAL_CONSTRUCTOR_ERROR flag, because the lack of a BMP file means the SDL_Surface pointer is set to NULL,
         * and you can't blit a NULL surface can you :P ? Also, the game will be using any images it loads, there is
         * no substitute for a BMP file. If it can't be used/found, then what's the point, you might not see something
         * important/useful. The game needs them.
         */
        class SurfaceCreationError {};

        Surface() { this->me = NULL; } // TODO: In here or in .cpp or initializer list???

        /* This constructor constructs a Surface object and uses SDL_LoadBMP to make the Surface hold a bitmap image.
         * If the bitmap file fails to load for whatever reason, be it a non existant file or not a BMP file or
         * whatever, the constructor will throw a SurfaceCreationError.
         *
         * The image is originally held in a temporary SDL_Surface, and if the load succeeds then it is copied into
         * the class' private SDL_Surface with a call to SDL_DisplayFormat to ensure the surface has the same format as
         * the display surface. This way blitting is done as fast as possible since SDL does not have to convert the
         * surface every time it wants to blit it.
         *
         * BmpFilePath is the file path to a bitmap image file.
         *
         * TODO: The function currently uses SDL_DisplayFormat() which works on 24-bit images and since pretty much all
         *       graphics cards these days deal with 32-bit (alpha channel support), using SDL_DisplayFormatAlpha()
         *       would be faster. Maybe I should switch to using that?
         */
        Surface(const std::string BMPFilePath);

        /* Destructs a Surface object and frees it.
         * That's really all it does... frees the surface.
         */
        ~Surface();

        /* This entire surface gets blitted onto Destination. If this surface is larger than the destinated surace,
         * then clipping will occur, as usual removing the bottom-most and right-most parts of the image.
         *
         * Destination is the Address of the surface on which this surface is to be blitted on.
         * The function returns 0 on success, otherwise -1. If any of the two surfaces were in video memory, it returns
         * -2, but the Blit() function takes care of that by reloading the surface and re-blitting.
         *
         *  And... that was the SDL_BlitSurface() function heh. As for Blit() here, it returns a bool to signal success
         *  or failure. Probably not gonna use it for anything but debug purposes though...
         *
         * TODO: Since there will be a lot of repeated code, probably think of letting all Blit()'s call a single Blit()
         */
        bool Blit(const Surface *Destination);

        /* Blits the Surface onto Destination at co-ordinates (X,Y). */
        bool Blit(const Surface *Destination, int DestXOffset, int DestYOffset);

    public:
        SDL_Surface *me; // Declared protected so it can be inherited by the Display and FontSurface classes.

    private:
        bool RealBlit(const Surface *Destination, SDL_Rect *SourceRect, SDL_Rect *DestRect); // Used internally.
        std::string FilePath; // Maybe remove as it'll be stored somewhere else and you'll end up with TONS of them when creating bullets.
};

};

#endif
