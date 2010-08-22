#include "SDLWrap_SDLEngine.hpp"
#include "SDLWrap_Display.hpp"
#include "SDLWrap_Font.hpp"
#include "SDLWrap_Color.hpp"
#include "SDLWrap_FontSurface.hpp"

using namespace SDLWrap;

int
main()
{
    SDLEngine engine(SDLEngine::EVERYTHING);
    Display screen(640, 480, 0, Display::HWSURFACE | Display::DOUBLEBUF);
    Font_SPtr mikachan26(new Font("mikachan.ttf", 26));
    Color aqua(0, 192, 192);
    FontSurface sometext1("Woah! cool.", mikachan26, aqua);
    FontSurface sometext2("I'm at the bottom!", mikachan26, aqua);
    sometext1.RenderTextSolid();
    sometext2.RenderTextSolid();
    sometext1.Blit(screen, 100, 100);
    sometext2.Blit(screen, 340, 400);
    screen.Flip();
    std::cout << "boost::shared_ptr<Font>::use_count(): " << mikachan26.use_count() << '\n';
    SDL_Delay(2500);
    return 7;
}
