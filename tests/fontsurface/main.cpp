#include "SDLWrap_SDLEngine.hpp"
#include "SDLWrap_Display.hpp"
#include "SDLWrap_Font.hpp"
#include "SDLWrap_FontSurface.hpp"
#include "SDLWrap_Color.hpp"
#include "boost/shared_ptr.hpp"
#include <iostream>
using namespace SDLWrap;

int
main()
{
    SDLEngine engine(SDLEngine::EVERYTHING);
    Display screen(640, 480, 0, Display::SWSURFACE);
    Font_SPtr philosopher(new Font("philosopher.ttf", 22));
    Color aquablue(0, 192, 192);
    FontSurface some_text("Finally xD", philosopher, aquablue);
    some_text.RenderTextSolid();
    some_text.Blit(screen);
    screen.Flip();
    SDL_Delay(2000);
    std::cout << "shared_ptr::refcount=" << philosopher.use_count() << '\n';
    return 6;
}
