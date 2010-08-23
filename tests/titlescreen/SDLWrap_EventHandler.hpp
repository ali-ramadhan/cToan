#ifndef _SDLWRAP_EVENTHANDLER_H_
#define _SDLWRAP_EVENTHANDLER_H_

#include <iostream>
#include "SDL/SDL.h"

namespace SDLWrap {

/* This class takes care of all events, reading them, handling them etc. The plan is to have the game singleton inherit
 * from this class so all actual event handling is taken care by the derived class. This class simply acts as a wrapper
 * around the SDL_PollEvent() function and all the On* functions that detect and handle the individual unique events.
 * Since I don't know what they'll be doing yet, the plan is to declare all On* functions that I need as pure virtual
 * functions. This class won't be using any of them, it's all up to the singleton.
 */
class EventHandler
{
    public:
        /* Empty constructor and destructor... */
        EventHandler();
        ~EventHandler();

        /* This function is responsible for handling all calls to the On*() functions. Since they're all virtual for
         * now, it's not like it's gonna be doing much, but once the singleton overrides the pure virtual functions
         * then it can take control of any through this function. Well, more like this function will call the On*()
         * functions, which are all defined by the singleton.
         */
        void HandleEvent();

        /* Just a cheap wrapper around SDL_PollEvent. Just doing it to not type SDL_ :P */
        bool PollEvent();

        /* And... the virtuals :P Pretty much self explanatory as well. */
        /* Actually wait, seems I misunderstood pure virtual and virtual functions. If it's just simply virtual, like
         * what I'm doing here with my On*() functions, then they may be overridden, but pure virtual functions MUST be
         * overridden, which is not what I'm looking for...
         */
        virtual void OnQuit() {};
        virtual void OnKeyDown(SDLKey sym) {};

    private:
        SDL_Event Event;
};

};

#endif
