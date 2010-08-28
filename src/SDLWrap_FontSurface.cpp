#include "SDLWrap_FontSurface.hpp"

namespace SDLWrap {

void
FontSurface::RenderTextSolid()
{
    this->me = TTF_RenderText_Solid(meFont->me, SurfaceText.c_str(), ForegroundColor.me);
}

void
FontSurface::RenderTextBlended()
{
    this->me = TTF_RenderText_Blended(meFont->me, SurfaceText.c_str(), ForegroundColor.me);
}

void
FontSurface::SetForegroundColor(Color &NewFColor)
{
    this->ForegroundColor = NewFColor;
}

}
