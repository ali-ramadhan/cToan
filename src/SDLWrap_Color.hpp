#ifndef _SDLWRAP_COLOR_H_
#define _SDLWRAP_COLOR_H_

#include "SDL/SDL.h"

namespace SDLWrap {

/* This class is supposed to be a very simple wrapper around the SDL_Color struct, which represents an RGB color,
 * that's really about it...
 */
class Color {
    public:
        /* Just two expected constructors. Initialize the color to #000000 if empty constructor is called and with
         * values if called with 3 Uint8's.
         */
        Color();
        Color(Uint8 Red, Uint8 Green, Uint8 Blue);

        SDL_Color me;
};

};

#endif
