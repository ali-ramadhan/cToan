/* SDLWrap_SDLEngine.h
 *
 * This class is basically a C++ wrapper class around SDL Initialization & Shutdown, it takes care that everything SDL
 * related is shut down properly and is started up properly. It also takes care of SDL subsystems.
 *
 * IDEAS:
 * - Keep a copy of current flags in private section so that it can determine wether InitSubsystem and QuitSubsystem
 *   really need to do anything.
 * - Get rid of *SubSystem* 'cause you're not gonna be using them anyways <_<
 * - Include a function to set the video and audio driver through SDL_putenv();
 */

#ifndef _SDLWRAP_SDLENGINE_H_
#define _SDLWRAP_SDLENGINE_H_

#include <string>

#include "SDL/SDL.h"

#include "ErrorHandler.hpp"

namespace SDLWrap {

class SDLEngine
{
    public:
        /* This exception is thrown if SDL fails to initialize the core system or any subsystem.
         */
        class InitError {};

        /* All the SDL init flags are now stored in an enum, mainly to get rid of the SDL_ prefix on all of them
         * but also to make them members of the SDLEngine class and place them in the SDLWrap namespace, as
         * they'll probably be used around the program at some point, or at least in the init process of the main
         * singleton class.
         * I was gonna initially remove the INIT_ prefix from the last three members of the enum but that would
         * sort of be unlogical, why remove it on the last bunch, heh xD Just 'cause it sounds better is not
         * really a good excuse, I'll end up forgetting <_< Anyways, they're here to stay.
         * Also, remove the INIT_ prefix from all would've probably brought problems later, it's unlikely but
         * still possible that I'll declare somewhere else something called VIDEO, so yeah, just to make sure
         * I remember that they're ONLY for initializing SDL.
         * Ok well, changed my mind. Since I'll also be using the flags in QuitSubSystem() it doesn't really make
         * sense to leave the INIT_ in there so I removed it. Although the main reason is probably just that I
         * wanna make myself feel that I'm actually writing something useful, heh :P
         */
        enum {
            TIMER       = SDL_INIT_TIMER,
            AUDIO       = SDL_INIT_AUDIO,
            VIDEO       = SDL_INIT_VIDEO,
            CDROM       = SDL_INIT_CDROM,
            JOYSTICK    = SDL_INIT_JOYSTICK,
            // HAPTIC      = SDL_INIT_HAPTIC,      // Not available in sdl-1.2.* I think, I didn't find it in my SDL.h...
            NOPARACHUTE = SDL_INIT_NOPARACHUTE,
            EVENTTHREAD = SDL_INIT_EVENTTHREAD,
            EVERYTHING  = SDL_INIT_EVERYTHING
        };

        /* This constructor constructs an SDLEngine object without actually initializing any SDL subsystems. It
         * just does wrapper class specific stuff like setting CoreWasInitialized to false and making sure the
         * object is there whenever I wanna initialize SDL.
         */
        SDLEngine();

        /* This one obviously initializes SDL according to the OR'ed InitFlags sent in.
         */
        SDLEngine(Uint32) throw(InitError);

        /* The destructor calls Quit() to make sure the program exits cleanly and everything if I haven't already
         * called Quit(). Also might deal with a couple of private vars and such.
         */
        ~SDLEngine();

        /* In case the first constructor (the one that does not initialize any SDL subsystems is called), I'll
         * have to initialize SDL myself using this Init() function. Takes the same flags.
         */
        void Init(Uint32) throw(InitError);

        /* If I just wanna enable a specific subsystem later, I can use this function here.
         */
        void InitSubSystem(Uint32) throw(InitError);

        /* Called when the object is to be destroyed or if I just wanna quit early for some reason.
         */
        void Quit();

        /* I can call this if I ever wanna just quit out of one subsystem or a couple but not the core three.
         */
        void QuitSubSystem(Uint32);

        /* If I need to check wether (sub)system(s) were already initialized, I can just use this. Also, as per it's
         * default behaviour, if supplied with 0, it returns a mask of all initialized subsystems so I can use it
         * to keep track of Flags.
         */
        Uint32 WasInit(Uint32);

    private:
        Uint32 Flags; // Current flags being used by SDLEngine.

        bool CoreWasInitialized; // Used to see if calls to Quit() and Init() are valid, cheapest way of doing so.
        bool AlreadyShutdown;    // Also used to validate function calls, but this time only by the destructor.
};

}; // end namespace SDLWrap

#endif
