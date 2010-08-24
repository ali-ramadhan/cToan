#include "SDLWrap_FontSurface.hpp"

namespace SDLWrap {

void
FontSurface::RenderTextSolid()
{
    this->me = TTF_RenderText_Solid(meFont->me, SurfaceText.c_str(), TextColor->me);
}

};
