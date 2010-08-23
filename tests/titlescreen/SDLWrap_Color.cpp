#include "SDLWrap_Color.hpp"

namespace SDLWrap {

Color::Color()
{
    me.r = 0;
    me.g = 0;
    me.b = 0;
}

Color::Color(Uint8 Red, Uint8 Green, Uint8 Blue)
{
    me.r = Red;
    me.g = Green;
    me.b = Blue;
}

};
