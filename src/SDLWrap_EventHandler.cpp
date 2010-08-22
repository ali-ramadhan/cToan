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
    return SDL_PollEvent(this->Event);
}

void
EventHandler::HandleEvent()
{
    switch (this->Event->type) {
        case SDL_QUIT:
            OnQuit();
            break;

        default:
            ;
    }
}

};
