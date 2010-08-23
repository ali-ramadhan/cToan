#include "SDLWrap_EventHandler.hpp"

namespace SDLWrap {

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

bool
EventHandler::PollEvent()
{
    bool lol = SDL_PollEvent(&(this->Event));
//    std::cout << "lol: " << lol << '\n';
    return lol;
//    return SDL_PollEvent(this->Event);
}

void
EventHandler::HandleEvent()
{
//    std::cout << "&(this->Event): " << &(this->Event) << '\n';
    // No idea why I would need this, it shouldn't call HandleEvent() if no fucking event was found.
//    if (!this->Event)
//        return;

    switch (this->Event.type) {
        case SDL_KEYDOWN:
            OnKeyDown(Event.key.keysym.sym);
            break;

        case SDL_QUIT:
            OnQuit();
            break;

        default:
            ;
    }
}

};
