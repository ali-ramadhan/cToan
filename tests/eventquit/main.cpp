#include "SDLWrap_SDLEngine.hpp"
#include "SDLWrap_Display.hpp"
#include "SDLWrap_EventHandler.hpp"

using namespace SDLWrap;

class Singleton : public EventHandler
{
    public:
    SDLEngine *engine;
    Display *screen;
    Singleton() {
        engine = new SDLEngine(SDLEngine::EVERYTHING);
        screen = new Display(640, 480, 0, Display::HWSURFACE | Display::DOUBLEBUF);
    }
    void OnQuit() { delete engine; delete screen; Running = false;}
    bool Running;
};

int
main()
{
    Singleton app;
    app.Running = true;

    while (app.Running) {
        while (app.PollEvent()) {
            app.HandleEvent();
        }
    }
}
