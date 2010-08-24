#include "SDLWrap_FontSurface.hpp"

namespace SDLWrap {

void
FontSurface::RenderTextSolid()
{
    SDL_Color tmpColor;
    tmpColor.r = this->ForegroundColor->r;
    tmpColor.g = this->ForegroundColor->g;
    tmpColor.b = this->ForegroundColor->b;
    this->me = TTF_RenderText_Solid(meFont->me, SurfaceText.c_str(), tmpColor);
}

void
FontSurface::RenderTextBlended()
{
    SDL_Color tmpColor;
    tmpColor.r = this->ForegroundColor->r;
    tmpColor.g = this->ForegroundColor->g;
    tmpColor.b = this->ForegroundColor->b;
    this->me = TTF_RenderText_Blended(meFont->me, SurfaceText.c_str(), tmpColor);
}

}
