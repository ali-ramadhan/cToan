/* SDLWrap_SDLEngine.h
 *
 * IDEAS:
 * - Keep a copy of current flags in private section so that it can determine whether InitSubsystem and QuitSubsystem
 *   really need to do anything. Done with WasInit(0).
 * - Get rid of *SubSystem* 'cause you're not gonna be using them anyways <_<
 * - Include a function to set the video and audio driver through SDL_putenv();
 *
 * Changelog:
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

#include "ErrorHandler.hpp"

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

        /* All the SDL init flags are now stored in an enum, mainly to get rid of the SDL_ prefix on all of them
         * but also to make them members of the SDLEngine class and place them in the SDLWrap namespace, as
         * they'll probably be used around the program at some point, or at least in the init process of the main
         * singleton class.
         *
         * I was gonna initially remove the INIT_ prefix from the last three members of the enum but that would
         * sort of be illogical, why remove it on the last bunch, heh xD Just 'cause it sounds better is not
         * really a good excuse, I'll end up forgetting <_< Anyways, they're here to stay.
         *
         * Also, remove the INIT_ prefix from all would've probably brought problems later, it's unlikely but
         * still possible that I'll declare somewhere else something called VIDEO, so yeah, just to make sure
         * I remember that they're ONLY for initializing SDL.
         *
         * Ok well, changed my mind. Since I'll also be using the flags in QuitSubSystem() it doesn't really make
         * sense to leave the INIT_ in there so I removed it. Although the main reason is probably just that I
         * wanna make myself feel that I'm actually writing something useful, heh :P
         *
         * Oooh! Another reason to justify myself heh :P Since SDL uses #define to declare these flags, and if I'm
         * trying to debug my SDL program, it may be a problem with init flags, in which case I'll never know since
         * it'll complain about some value like 0x00008000 or something. Using enums will put the flags in the symbol
         * table so they can be debugged.
         */
        enum {
            TIMER       = SDL_INIT_TIMER,
            AUDIO       = SDL_INIT_AUDIO,
            VIDEO       = SDL_INIT_VIDEO,
            CDROM       = SDL_INIT_CDROM,
            JOYSTICK    = SDL_INIT_JOYSTICK,
            // HAPTIC      = SDL_INIT_HAPTIC,    // Not available in sdl-1.2.* I think, I didn't find it in my SDL.h...
            NOPARACHUTE = SDL_INIT_NOPARACHUTE,
            EVENTTHREAD = SDL_INIT_EVENTTHREAD,
            EVERYTHING  = SDL_INIT_EVERYTHING
        };

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

}; // end namespace SDLWrap

#endif
