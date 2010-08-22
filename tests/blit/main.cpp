#include "SDLWrap_SDLEngine.hpp"
#include "SDLWrap_Display.hpp"
#include "SDLWrap_Surface.hpp"

using namespace SDLWrap;

int
main()
{
    SDLEngine engine(SDLEngine::EVERYTHING);
    Display screen(1024, 768, 32, Display::HWSURFACE | Display::DOUBLEBUF);
    Surface coolpic("coolpic.bmp");
    coolpic.Blit(screen);
    screen.Flip();

    SDL_Delay(2000);
    return 4;
}
