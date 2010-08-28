#include <stack>
#include <vector>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "SDLWrap_SDLEngine.hpp"
#include "SDLWrap_Surface.hpp"
#include "SDLWrap_Display.hpp"
#include "SDLWrap_Font.hpp"
#include "SDLWrap_Color.hpp"
#include "SDLWrap_FontSurface.hpp"
#include "SDLWrap_Enums.hpp"
#include "Logger.hpp"`

using namespace SDLWrap;

class GameState
{
    public:
        virtual void operator()() = 0;
        static std::stack< boost::shared_ptr<GameState> > StateStack;

    protected:
        virtual void Logic() {}
        virtual void Render() {}
};

std::stack< boost::shared_ptr<GameState> > GameState::StateStack;

class MenuState : public GameState, public EventHandler
{
    public:
        MenuState() {
            CurrentChoice = 0;
            CursorPosition = 0;
            UpKeyDown = false;
            DownKeyDown = false;

            Surface *tmp_background = new Surface("gfx/titlescreen.bmp");
            Background.reset(tmp_background);

            Surface *tmp_cursor = new Surface("gfx/cursor.bmp");
            Cursor.reset(tmp_cursor);

            Font *tmp_textfont = new Font("fonts/optionlistfont.ttf");
            TextFont.reset(tmp_textfont);

            Color *tmp_textcolor = new Color(63, 107, 105);
            TextColor.reset(tmp_textcolor);

            FontSurface *tmp_newgame = new FontSurface("New Game", TextFont, *TextColor);
            NewGame.reset(tmp_newgame);
            NewGame->RenderTextBlended();
            MenuOptionList.push_back(tmp_newgame);

            FontSurface *tmp_settings = new FontSurface("Settings", TextFont, *TextColor);
            Settings.reset(tmp_settings);
            Settings->RenderTextBlended();
            MenuOptionList.push_back(tmp_settings);

            FontSurface *tmp_exitgame = new FontSurface("Exit Game", TextFont, *TextColor);
            ExitGame.reset(tmp_exitgame);
            ExitGame->RenderTextBlended();
            MenuOptionList.push_back(tmp_exitgame);
        }

        void operator()() {
            this->HandleEvent(); // Defined in the EventHandler class
            this->Logic();
            this->Render();
        }

    public: /* Event handlers */
        void OnKeyDown(Key sym) {
            switch (sym) {
                case KEY_UP:
                    UpKeyDown = true;
                    break;

                case KEY_DOWN:
                    DownKeyDown = true;
                    break;

                case KEY_RETURN:
                    switch (CurrentChoice) {
                        case 0:
                            GameState::StateStack.push(Singleton::Instance()->NewGame); //TODO
                            break;
                        case 1:
                            GameState::StateStack.push(Singleton::Instance()->Settings); // TODO
                            break;
                        case 2:
//                            GameState::StateStack.push(Singleton::Instance()->Exit);
                            GameState::StateStack.pop(); // Should I auto pop or push Exit which pops twice?
                            break;
                        default:
                            ;
                            break;
                    }
                    break;

                case KEY_ESCAPE:
                    GameState::StateStack.pop();
                    break;

                default:
                    ;
                    break;
            }
        }

        void OnKeyUp(Key sym) {
            switch (sym) {
                case KEY_UP:
                    UpKeyDown = false;
                    break;

                case KEY_DOWN:
                    DownKeyDown = false;
                    break;

                default:
                    ;
                    break;
            }
        }

    protected: /* Game state loop */
        void Logic() {
            if (UpKeyDown) {
                CurrentChoice--;
                if (CurrentChoice < 0)
                    CurrentChoice = 2; // User went above first option, loop around.
            }

            if (DownKeyDown) {
                CurrentChoice++;
                if (CurrentChoice > 2)
                    CurrentChoice = 0; // User tried to go below last (third) option, loop around.
            }

            CursorPosition = (CurrentChoice * 200) + 10;
        }

        void Render() {
            Background.Blit(*(Singleton::Instance()->Screen));
            for (unsigned int i = 0; i < MenuOptionList.size(); i++) {
                MenuOptionList[i]->Blit(*(Singleton::Instance()->Screen), 500, (i * 200) + 10); }
            Cursor.Blit(*(Singleton::Instance()->Surface), 450, CursorPosition);
        }

    private:
        boost::scoped_ptr<Surface> Background;
        boost::scoped_ptr<Surface> Cursor;
        
        boost::shared_ptr<Font> TextFont;
        boost::scoped_ptr<Color> TextColor;
        shared_ptr<FontSurface> NewGame;
        shared_ptr<FontSurface> Settings;
        shared_ptr<FontSurface> ExitGame;
        std::vector< boost::shared_ptr<FontSurface > MenuOptionList;

        int CurrentChoice;
        int CursorPosition;
        bool UpKeyDown, DownKeyDown;
};

class NewGameState : public GameState
{
    // Holy shit this one is gonna be BIG if the settings was 220+ lines.
};

class SettingsState : public GameState, public EventHandler
{
    /* - Different background
     * - List of 3 or 4 options (FontSurfaces)
     * - Each with their own options like (resolution: 800x600, 1024x768, etc.)
     * - Up and down to change options.
     * - Left/Right or Space to toggle options
     * - Option looping, yes
     * - Different colored font for chosen options. (Purple = chosen, orange = not) etc. example
     */

    public:
        SettingsState() {
            CurrentChoice = ResolutionChoice = DifficultyChoice = FullscreenChoice = 0;
            UpKeyDown = DownKeyDown = RightKeyDown = LeftKeyDown = false;
            CursorPosition = 0;

            Surface *tmp_background = new Surface("gfx/settingsbackground.bmp");
            Background.reset(tmp_background);

            Surface *tmp_cursor = new Surface("gfx/settingscursor.bmp");
            Cursor.reset(tmp_cursor);

            Font *tmp_textfont = new Font("fonts/optionlistfont.ttf", 26);
            TextFont.reset(tmp_textfont);

            Color *tmp_textcolor = new Color(46, 124, 49);
            TextColor.reset(tmp_color);

            FontSurface *tmp_resolution = new FontSurface("Resolution", TextFont, *TextColor);
                FontSurface *tmp_res1280 = new FontSurface("1280x1024", TextFont, *TextColor);
                FontSurface *tmp_res1024 = new FontSurface("1024x768", TextFont, *TextColor);
                FontSurface *tmp_res800  = new FontSurface("800x600", TextFont, *TextColor);

            FontSurface *tmp_difficulty = new FontSurface("Difficulty", TextFont, *TextColor);
                FontSurface *tmp_pisseasy = new FontSurface("Piss Easy", TextFont, *TextColor);
                FontSurface *tmp_theusual = new FontSurface("The Usual", TextFont, *TextColor);
                FontSurface *tmp_fuckme   = new FontSurface("Fuck Me", TextFont, *TextColor);

            FontSurface *tmp_fullscreen = new FontSurface("Fullscreen", TextFont, *TextColor);
                FontSurface *tmp_yes = new FontSurface("Yes", TextFont, *TextColor);
                FontSurface *tmp_no = new FontSurface("No", TextFont, *TextColor);

            FontSurface *tmp_back = new FontSurface("Back", TextFont, *TextColor);

            Resolution.reset(tmp_resolution);
            Res1280.reset(tmp_1280);
            Res1024.reset(tmp_1024);
            Res800.reset(tmp_800);
            Difficulty.reset(tmp_difficulty);
            PissEasy.reset(tmp_pisseasy);
            TheUsual.reset(tmp_theusual);
            FuckMe.reset(tmp_fuckme);
            Fullscreen.reset(tmp_fullscreen);
            Yes.reset(tmp_yes);
            No.reset(tmp_no);
            Back.reset(tmp_back);

            SettingsOptionList.push_back(Resolution);
            SettingsOptionList.push_back(Res1280);
            SettingsOptionList.push_back(Res1024);
            SettingsOptionList.push_back(Res800);
            SettingsOptionList.push_back(Difficulty);
            SettingsOptionList.push_back(PissEasy);
            SettingsOptionList.push_back(TheUsual);
            SettingsOptionList.push_back(FuckMe);
            SettingsOptionList.push_back(Fullscreen);
            SettingsOptionList.push_back(Yes);
            SettingsOptionList.push_back(No);
            SettingsOptionList.push_back(Back);

            for (unsigned int i = 0; i < SettingsOptionList.size(); i++) {
                SettingsOptionList[i]->RenderTextBlended(); }
        }

        void OnKeyDown(Key sym) {
            switch (sym) {
                case KEY_UP:
                    UpKeyDown = true;
                    break;

                case KEY_DOWN:
                    DownKeyDown = true;
                    break;

                case KEY_RIGHT:
                    RightKeyDown = true;
                    break;

                case KEY_LEFT:
                    LeftKeyDown = true;
                    break;

                case KEY_RETURN:
                    switch (CurrentChoice) {
                        case 3:
                            GameState::StateStack.pop();
                            break;

                        default:
                            ;
                            break;
                    }
                    break;

                case KEY_ESCAPE:
                    GameState::StateStack.pop();
                    break;

                default:
                    ;
                    break;
            }
        }

    protected:
        Logic() {
            if (UpKeyDown) {
                CurrentChoice--;
                if (CurrentChoice < 0)
                    CurrentChoice = 3;
            }

            if (DownKeyDown) {
                CurrentChoice++;
                if (CurrentChoice > 3)
                    CurrentChoice = 0;
            }

            if (RightKeyDown) {
                switch (CurrentChoice) {
                    case 0:
                        ResolutionChoice++;
                        if (ResolutionChoice > 2)
                            ResolutionChoice = 0;
                        break;

                    case 1:
                        DifficultyChoice++;
                        if (DifficultyChoice > 2)
                            DifficultyChoice = 0;
                        break;

                    case 2:
                        FullscreenChoice++;
                        if (FullscreenChoice > 1)
                            DifficultyChoice = 0;
                        break;

                    default:
                        ;
                        break;
                }
            }

            if (LeftKeyDown) {
                switch (CurrentChoice) {
                    case 0:
                        ResolutionChoice--;
                        if (ResolutionChoice < 0)
                            ResolutionChoice = 2;
                        break;

                    case 1:
                        DifficultyChoice--;
                        if (DifficultyChoice < 0)
                            DifficultyChoice = 2;
                        break;

                    case 2:
                        FullscreenChoice++;
                        if (FullscreenChoice < 0)
                            DifficultyChoice = 1;
                        break;

                    default:
                        ;
                        break;
                }
            }
            CursorPosition = (CurrentChoice + 1) * 100;
        }


        void Render() {
            Background.Blit(*(Singleton::Instance->Screen));
            Resolution.Blit(*(Singleton::Instance->Screen), 110, 100);
            Difficulty.Blit(*(Singleton::Instance->Screen), 110, 200);
            Fullscreen.Blit(*(Singleton::Instance->Screen), 110, 300);
            Back.Blit(*(Singleton::Instance->Screen), 110, 400);
            Cursor.Blit(*(Singleton::Instance->Screen), 30, CursorPosition);
            // Blit the choices to the right.
            //  If chosen, color c2
            //  If not, color c1
            // Too much trouble for now though, come back later. TODO
            // Maybe redesign the vectors.
        }

    priviate:
        int CurrentChoice, ResolutionChoice, DifficultyChoice, FullscreenChoice;
        bool UpKeyDown, DownKeyDown, LeftKeyDown, RightKeyDown;
        int CursorPosition;

        boost::scoped_ptr<Surface> Background;
        boost::scoped_ptr<Surface> Cursor;

        boost::shared_ptr<Font> TextFont;
        boost::scoped_ptr<Color> TextColor;
        boost::scoped_ptr<color> ChosenTextColor;

        boost::shared_ptr<FontSurface> Resolution;
        boost::shared_ptr<FontSurface> Res1280;
        boost::shared_ptr<FontSurface> Res1024;
        boost::shared_ptr<FontSurface> Res800;

        boost::shared_ptr<FontSurface> Difficulty;
        boost::shared_ptr<FontSurface> PissEasy;
        boost::shared_ptr<FontSurface> TheUsual;
        boost::shared_ptr<FontSurface> FuckMe;

        boost::shared_ptr<FontSurface> Fullscreen;
        boost::shared_ptr<FontSurface> Yes;
        boost::shared_ptr<FontSurface> No;

        boost::shared_ptr<FontSurface> Back;

        std::vector< boost::shared_ptr<FontSurface> > SettingsOptionList;

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
    private:
        /* Constructor + instance pointer */
        static Singleton *InstancePtr;
        Singleton() {
            // Pushing the exit state first.
            ExitState *tmp_exit = new ExitState();
            Exit.reset(tmp_exit);
            GameState::StateStack.push(Exit);

            // Menu pushed next and no more, it's the first state anyways.
            MenuState *tmp_menu = new MenuState();
            Menu.reset(tmp_menu);
            GameState::StateStack.push(Menu);

            SDLEngine *tmp_engine = new SDLEngine(VIDEO);
            Engine.reset(tmp_engine);

            Display *tmp_screen = new Display(SWSURFACE);
            Display.reset(tmp_screen);
        }

    public:
        /* Instance Management*/
        static Singleton* Instance() {
            if (InstancePtr == NULL)
                InstancePtr = new Singleton();
            return InstancePtr;
        }

        /* States */
        boost::shared_ptr<ExitState> Exit;
        boost::shared_ptr<MenuState> Menu;
        boost::shared_ptr<NewGameState> NewGame;  //TODO
        boost::shared_ptr<SettingsState> Settings; //TODO

    private:
        /* SDL Objects */
        boost::scoped_ptr<SDLEngine> Engine;
        boost::scoped_ptr<Display>   Screen;
};

Singleton *Singleton::InstancePtr = NULL;

int
main()
{
    Singleton::Instance(); // Setting up the singleton.
    while (!GameState::StateStack.empty()) {
        GameState::StateStack.top()(); // Syntax looks weird but it works xD
    }

    return 10;
}
