/* SDLWrap_Surface.hpp
 *
 * Changelog:
 * 24/08/2010: - Changed the Blit() functions so they take const references to Surfaces instead of const pointers to
 *               Surfaces. I'll be using a lot of scoped and shared pointers and dereferencing them is cleaner than
 *               calling their get() function to get a pointer.
 *
 * 23/08/2010: - Removed the private FilePath var. It'll only clutter around since I don't even use it yet.
 *             - Added a default constructor to please derived classes that call it.
 *             - BMPFilePath -> FilePath, might be more than just BMP's later anyways.
 *             - Changed to using const pointers to Surfaces in Blit().
 */
#ifndef _SDLWRAP_SURFACE_H_
#define _SDLWRAP_SURFACE_H_

#include <string>

#include <SDL/SDL.h>

#include "Logger.hpp"

namespace SDLWrap {

/* This class acts as a wrapper around the SDL_Surface structure and defines the functions you would normally use with
 * SDL_Surfaces such as SDL_BlitSurface() and also provides useful shortcuts like a constructor that takes a BMP file
 * path.
 */
class Surface
{
    public:
        /* When caught it creates an error std::string which it sends to the Error Handler with the
         * CONSTRUCTOR + FATAL flags, because the lack of a BMP file means the SDL_Surface pointer is set to NULL,
         * and you can't blit a NULL surface can you :P ? Also, the game will be using any images it loads, there is
         * no substitute for a BMP file. If it can't be used/found, then what's the point, you might not see something
         * important/useful. The game needs them.
         */
        class SurfaceCreationError {};

        /* Creating a default constructor just in case since FontSurface will call it so might as well do some bare
         * minimum stuff. Some = the only xD
         */
        Surface() : me(NULL) {}

        /* This constructor constructs a Surface object and uses SDL_LoadBMP to make the Surface hold a bitmap image.
         * If the bitmap file fails to load for whatever reason, be it a non existant file or not a BMP file or
         * whatever, the constructor will throw a SurfaceCreationError.
         *
         * The image is originally held in a temporary SDL_Surface, and if the load succeeds then it is copied into
         * the class' private SDL_Surface with a call to SDL_DisplayFormat to ensure the surface has the same format as
         * the display surface. This way blitting is done as fast as possible since SDL does not have to convert the
         * surface every time it wants to blit it.
         *
         * TODO: The function currently uses SDL_DisplayFormat() which works on 24-bit images and since pretty much all
         *       graphics cards these days deal with 32-bit (alpha channel support), using SDL_DisplayFormatAlpha()
         *       would be faster. Maybe I should switch to using that?
         */
        Surface(const std::string FilePath);

        /* Destructs a Surface object and frees it.
         * That's really all it does... frees the surface.
         */
        ~Surface();

        /* This entire surface gets blitted onto Destination. If this surface is larger than the destinated surace,
         * then clipping will occur, as usual removing the bottom-most and right-most parts of the image.
         *
         * It returns a bool to signal success or failure. Probably not gonna use it for anything but debug purposes
         * though...
         */
        bool Blit(Surface &Destination);

        /* Blits the Surface onto Destination at co-ordinates (X,Y). */
        bool Blit(Surface &Destination, int DestXOffset, int DestYOffset);

    protected:
        SDL_Surface *me; // Declared protected so it can be inherited by the Display and FontSurface classes.

    private:
        /* All the public blit functions call this function internally to do the actual blitting, so the public ones
         * just setup all the variables and structures needed to Blit correctly, then pass it to here. It's also to
         * keep all error checking in one place since calling SDL_BlitSurface() can return -2 if the video memory was
         * lost, in which case, the surface must be reloaded/reblitted which requires extra work and possible quite a
         * bit of extra code, so I decided to keep everything here.
         */
        bool RealBlit(Surface &Destination, SDL_Rect *SourceRect, SDL_Rect *DestRect); // Used internally.
};

};

#endif
