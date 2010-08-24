#include <iostream>
#include <vector>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "SDLWrap_SDLEngine.hpp"
#include "SDLWrap_EventHandler.hpp"
#include "SDLWrap_Surface.hpp"
#include "SDLWrap_Display.hpp"
#include "SDLWrap_Font.hpp"
#include "SDLWrap_FontSurface.hpp"
#include "SDLWrap_Color.hpp"

using namespace SDLWrap;

class TitleScreen : public EventHandler
{
    public:
        TitleScreen() {
            Running = true;
            CurrentChoice = 0;
            
            SDLEngine *tmp_engine = new SDLEngine(EVERYTHING);
            Display *tmp_screen = new Display(800, 600, 32, SWSURFACE);
            Surface *tmp_background = new Surface("titlescreen.bmp");
            Font *tmp_textFont = new Font("titlescreenfont.ttf", 30);
            Surface *tmp_cursor = new Surface("cursor.bmp");
            Color *tmp_textColor = new Color(63, 107, 105);

            this->engine.reset(tmp_engine);
            this->screen.reset(tmp_screen);
            this->background.reset(tmp_background);
            this->textFont.reset(tmp_textFont);
            this->cursor.reset(tmp_cursor);
            this->textColor.reset(tmp_textColor);
        }

        void initLabels() {
            boost::shared_ptr<FontSurface> new_game(new FontSurface("New Game", this->textFont, *(this->textColor)));
            boost::shared_ptr<FontSurface> load_game(new FontSurface("Load Game", this->textFont, *(this->textColor)));
            boost::shared_ptr<FontSurface> options(new FontSurface("Options", this->textFont, *(this->textColor)));
            boost::shared_ptr<FontSurface> exit_game(new FontSurface("Exit Game", this->textFont, *(this->textColor)));
            this->textLabels.push_back(new_game);
            this->textLabels.push_back(load_game);
            this->textLabels.push_back(options);
            this->textLabels.push_back(exit_game);
            for (unsigned int i = 0; i < textLabels.size(); i++) { textLabels[i]->RenderTextBlended(); }
        }

        void blitEverything() {
            background->Blit(*screen);
            cursor->Blit(*screen, 450, (CurrentChoice * 150) + 10);
            for (unsigned int i = 0; i < textLabels.size(); i++) { textLabels[i]->Blit(*screen, 500, (i * 150) + 10); }
            screen->Flip();
        }

        void OnQuit() { Running = false; }

        void choicePrint() {
            switch (CurrentChoice) {
                case 0:
                    std::cout << "New Game\n";
                    break;

                case 1:
                    std::cout << "Load Game\n";
                    break;

                case 2:
                    std::cout << "Options\n";
                    break;

                case 3:
                    std::cout << "Exit Game\n";
                    OnQuit();
                    break;
            }
        }

        void OnKeyDown(Key sym) {
            switch (sym) {
                case KEY_DOWN:
                    if (CurrentChoice < 3) { CurrentChoice++; std::cout << "CurrentChoice: " << CurrentChoice << '\n'; }
                    else { CurrentChoice = 0; }
                    break;

                case KEY_UP:
                    if (CurrentChoice > 0) { CurrentChoice--; std::cout << "CurrentChoice: " << CurrentChoice << '\n'; }
                    else { CurrentChoice = 3; }
                    break;

                case KEY_ESCAPE:
                    OnQuit();
                    break;

                case KEY_RETURN:
                case KEY_Z:
                    choicePrint();
                    break;

                default:
                    ;
                    break;
            }
        }

    private:
        boost::scoped_ptr<SDLEngine> engine;
        boost::scoped_ptr<Display> screen;
        boost::scoped_ptr<Surface> background;
        boost::scoped_ptr<Surface> cursor;

        boost::shared_ptr<Font> textFont;
        boost::scoped_ptr<Color> textColor;
        std::vector< boost::shared_ptr<FontSurface> > textLabels;

    public:
        bool Running;
        int CurrentChoice;
};

int
main()
{
    TitleScreen app;
    app.initLabels();
    while (app.Running) {
        while (app.PollEvent()) {
            app.HandleEvent();
        }
        app.blitEverything();
        SDL_Delay(16);
    }
    return 9;
}
