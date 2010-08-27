#include <stack>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "SDLWrap_SDLEngine.hpp"
#include "SDLWrap_Display.hpp"
#include "SDLWrap_Enums.hpp"
#include "Logger.hpp"`

using namespace SDLWrap;

class GameState
{
    public:
        virtual void operator()() = 0;
        static std::stack< boost::shared_ptr<GameState> > StateStack;

    protected:
        virtual void HandleEvent() {}
        virtual void Logic() {}
        virtual void Render() {}
};

std::stack< boost::shared_ptr<GameState> > GameState::StateStack;

class MenuState : public GameState
{
    public:
        MenuState() {
            Surface *tmp_background = new Surface("gfx/titlescreen.bmp");
            Background.reset(tmp_background);

            Surface *tmp_cursor = new Surface("gfx/cursor.bmp");
            Cursor.reset(tmp_cursor);
        }

    private:
        boost::scoped_ptr<Surface> Background;
        boost::scoped_ptr<Surface> Cursor;
};

class NewGame : public GameState
{
};

class Settings : public GameState
{
};

class ExitState : public GameState
{
    public:
        void operator()() {
            StateStack.pop(); // Popping self off to empty the stack and exit the game loop.
        }
};

class Singleton : public EventHandler
{
    public:
        Singleton() {
            // Pushing the exit state first.
            ExitState *tmp_exit = new ExitState();
            Exit.reset(tmp_exit);
            GameState::StateStack.push(Exit);

            // Menu pushed next and no more, it's the first state anyways.
            MenuState *tmp_menu = new Menustate();
            Menu.reset(tmp_menu);
            GameState::StateStack.push(Menu);

            SDLEngine *tmp_engine = new SDLEngine(VIDEO);
            Engine.reset(tmp_engine);

            Display *tmp_screen = new Display(SWSURFACE);
            Display.reset(tmp_screen);
        }
        ~Singleton();

        /* STATES */
        boost::shared_ptr<ExitState> Exit;
        boost::shared_ptr<MenuState> Menu;

    private:
        /* SDL Objects */
        boost::scoped_ptr<SDLEngine> Engine;
        boost::scoped_ptr<Display>   Screen;
}

int
main()
{
    Singleton app;
    while (!GameState::StateStack.empty()) {
        GameState::StateStack.top()(); // Syntax looks weird but it works xD
    }

    return 10;
}
