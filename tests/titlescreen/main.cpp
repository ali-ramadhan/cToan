#include <boost/scoped_ptr.hpp>
#include "SDLWrap_SDLEngine.hpp"
#include "SDLWrap_EventHandler.hpp"

using namespace SDLWrap;

class TitleScreen : public EventHandler
{
    public:
        TitleScreen() {
            SDLEngine *tmp_engine = new SDLEngine(SDLEngine::EVERYTHING);
            Display *tmp_screen = new Display(800, 600, 32, Display::HWSURFACE | Display::DOUBLEBUF);
            Surface *tmp_background = new Surface("titlescreen.bmp");

            this->engine.reset(tmp_engine);
            this->screen.reset(tmp_screen);
        }
        virtual ~TitleScreen();

    private:
        boost::scoped_ptr<SDLEngine> engine;
        boost::scoped_ptr<Display> screen;
        boost::scoped_ptr<Surface> background;
};
