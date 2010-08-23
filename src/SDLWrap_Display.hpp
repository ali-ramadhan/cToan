#ifndef _SDLWRAP_DISPLAY_H_
#define _SDLWRAP_DISPLAY_H_

#include "SDL/SDL.h"

#include "SDLWrap_Surface.hpp"
#include "ErrorHandler.hpp"

namespace SDLWrap {

/* This class is a speacil purpose surface, it represents the actual video frame buffer memory, so it must be created
 * first.
 */

class Display : public Surface {
    public:
        /* All flags that can be sent to SetVideoMode, or in this case, the Display constructor, are gathered and
         * displayed here. To be fair, they can be used in plain Surfaces but that's limited to a few, the first
         * three of them, or was it four? Anyways, it requires CreateRGBSurface() which I'm unlikely to use, so
         * why put them there?
         */
        enum {
            SWSURFACE  = SDL_SWSURFACE,
            HWSURFACE  = SDL_HWSURFACE,
            ASYNCBLIT  = SDL_ASYNCBLIT,
            ANYFORMAT  = SDL_ANYFORMAT,
            HWPALETTE  = SDL_HWPALETTE,
            DOUBLEBUF  = SDL_DOUBLEBUF,
            FULLSCREEN = SDL_FULLSCREEN,
            OPENGL     = SDL_OPENGL,
            OPENGLBLIT = SDL_OPENGLBLIT,
            RESIZABLE  = SDL_RESIZABLE,
            NOFRAME    = SDL_NOFRAME
        };

        /* Really self explanatory constructor, c'mon ^^'
         * All that's worth noting is that it throws a SurfaceCreationError if it can't create the Display surface.
         */
        Display(int Width, int Height, int BPP, Uint32 Flags);

        /* If the hardware supports double buffering or if the Display was constructed with the HWSURFACE flag then
         * this function sets up a flip and returns. The hardware will wait for vertical retrace, and swaps video
         * buffers before the next video surface blit or lock will return. If SWSURFACE is set on the Display, then it
         * simply calls SDL_UpdateRect(this->me, 0, 0, 0, 0).
         *
         * A software screen surface is also updated automatically when parts of a SDL window are redrawn, caused by
         * overlapping windows or by restoring from an iconified state. As a result there is no proper double buffer
         * behavior in windowed mode for a software screen, in contrast to a full screen software mode.
         *
         * You must pass the DOUBLEBUF flag to the Display constructor for the function to perform hardware flipping.
         */
        bool Flip();
};

};

#endif
