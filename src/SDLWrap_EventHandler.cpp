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
    return SDL_PollEvent( &(this->Event) );
}

void
EventHandler::HandleEvent()
{
    switch (this->Event.type) {
        case SDL_KEYDOWN:
            OnKeyDown((Key) Event.key.keysym.sym);
            break;

        case SDL_KEYUP:
            OnKeyUp((key) Event.key.keysym.sym);
            break;

        case SDL_QUIT:
            OnQuit();
            break;

        default:
            ;
    }
}

};
