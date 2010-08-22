#include "SDLWrap_FontSurface.hpp"

namespace SDLWrap {

FontSurface::FontSurface(std::string Text, Font_SPtr Font, Color ColorOfText)
{
    this->SurfaceText = Text;
    this->meFont = Font;
    this->TextColor = ColorOfText;
}

FontSurface::~FontSurface()
{
}

void
FontSurface::RenderTextSolid()
{
    this->me = TTF_RenderText_Solid(meFont->me, SurfaceText.c_str(), TextColor.me);
}

};
