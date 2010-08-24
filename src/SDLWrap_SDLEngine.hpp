/* SDLWrap_SDLEngine.h
 *
 * IDEAS:
 * - Keep a copy of current flags in private section so that it can determine whether InitSubsystem and QuitSubsystem
 *   really need to do anything. Done with WasInit(0).
 * - Get rid of *SubSystem* 'cause you're not gonna be using them anyways <_<
 * - Include a function to set the video and audio driver through SDL_putenv();
 *
 * Changelog:
 * 24/08/10: - Moved the enum with the init flags to the enum header.
 *
 * 23/08/10: - Switched to using constructor initializers rather than assignment.
 *           - Removed the useless exception specification on some of the functions.
 *           - Removed the InitSubSystem/QuitSubSystem functions. I'll add 'em later if I need them.
 *           - Also removed the Init and Quit functions. I'll be dynamically allocating, will never use them.
 *           - Removed the private Flags. More efficient to just call WasInit() whenever I want them.
 *           - Removed private bool AlreadyShutdown. There's no Quit() anymore so it's useless.
 */

#ifndef _SDLWRAP_SDLENGINE_H_
#define _SDLWRAP_SDLENGINE_H_

#include <string>

#include <SDL/SDL.h>

#include "SDLWrap_Enums.hpp"
#include "Logger.hpp"

namespace SDLWrap {

/* This class is basically a C++ wrapper class around SDL Initialization & Shutdown, it takes care that everything SDL
 * related is shut down properly and is started up properly. It also takes care of SDL subsystems.
 */
class SDLEngine
{
    public:
        /* This exception is thrown if SDL fails to initialize the core system or any subsystem.
         */
        class InitError {};

        /* This constructor constructs an SDLEngine object without actually initializing any SDL subsystems. It
         * just does wrapper class specific stuff like setting CoreWasInitialized to false and making sure the
         * object is there whenever I wanna initialize SDL.
         */
        SDLEngine() {}

        /* This one obviously initializes SDL according to the OR'ed InitFlags sent in.
         */
        SDLEngine(Uint32 InitFlags);

        /* The destructor calls Quit() to make sure the program exits cleanly and everything if I haven't already
         * called Quit(). Also might deal with a couple of private vars and such.
         */
        ~SDLEngine();

        /* If I need to check wether (sub)system(s) were already initialized, I can just use this. Also, as per it's
         * default behaviour, if supplied with 0, it returns a mask of all initialized subsystems so I can use it
         * to keep track of Flags.
         */
        Uint32 WasInit(Uint32 InitFlags);

    private:
        bool CoreWasInitialized; // Used to see if calls to Quit() and Init() are valid, cheapest way of doing so.
};

}

#endif
