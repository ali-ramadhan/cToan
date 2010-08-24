/* SDLWrap_Enums.hpp
 *
 * Just a header file to keep all the enums. Keeping everything in their own class and prefixing them with the class
 * name and the scope operator is a bit stupid. Everything is in the SDLWrap namespace so I shouldn't worry about name
 * clashes either.
 */

#ifndef _SDLWRAP_ENUMS_H_
#define _SDLWRAP_ENUMS_H_

namespace SDLWrap {

/* All the SDL init flags are now stored in this enum, mainly to get rid of the SDL_ prefix on all of them
 * but also to place them in the SDLWrap namespace, as they'll probably be used around the program at some point,
 * or at least in the init process of the main singleton class.
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

/* All flags that can be sent to SetVideoMode, or in this case, the Display constructor, are gathered and
 * displayed here. They can also be used on normal surfaces, which I may or may not used later on, but for now
 * they're staying in this header file.
 */

enum {
    SWSURFACE  = SDL_SWSURFACE,
    HWSURFACE  = SDL_HWSURFACE,
    ASYNCBLIT  = SDL_ASYNCBLIT,
    ANYFORMAT  = SDL_ANYFORMAT,
    HWPALETTE  = SDL_HWPALETTE,
    DOUBLEBUF  = SDL_DOUBLEBUF,
    FULLSCREEN = SDL_FULLSCREEN,
    OPENGL     = SDL_OPENGL,
    OPENGLBLIT = SDL_OPENGLBLIT,
    RESIZABLE  = SDL_RESIZABLE,
    NOFRAME    = SDL_NOFRAME
};

/* This monster here is the keysym enum xD And the main reason why I moved all the enums here. Firstly it's annoying to
 * prefix EventHandler:: before EVERY SINGLE KEY so might as well place this here. The only annoyance will be that I
 * prefixed everything with KEY_. That's because some of the keys, when stripped of their SDLK_ name are single numbers
 * like SDLK_8, which can't be an enum. It might be a good idea though... Pretty much every capital letter name
 * would've been taken in the global SDLWrap namespace :P
 *
 * The way it works is that I'll just enum the keys I really need, which includes the usual ones like RETURN, SPACE,
 * etc. I don't wanna end up with some huge list of enum'ed keys of which I use only 5%. With that said, the list is in
 * the order the keys are defined in the SDL_keysym.h header.
 *
 * Uppercase letters are skipped as you can get them by checking for Caps lock or the KEYMOD for any of the two SHIFT's.
 */
enum {
    /* ASCII mapped keys */
    KEY_BACKSPACE = SDLK_BACKSPACE,
    KEY_RETURN    = SDLK_RETURN,
    KEY_ESCAPE    = SDLK_ESCAPE,
    KEY_SPACE     = SDLK_SPACE,

    /* Lowercase letters */
    KEY_C = SDLK_c,
    KEY_X = SDLK_x,
    KEY_Z = SDLK_z,

    /* Arrow keys */
    KEY_UP    = SDLK_UP,
    KEY_DOWN  = SDLK_DOWN,
    KEY_RIGHT = SDLK_RIGHT,
    KEY_LEFT  = SDLK_LEFT,

    /* Key state modifiers */
    KEY_RSHIFT = SDLK_RSHIFT,
    KEY_LSHIFT = SDLK_LSHIFT
};

}

#endif
