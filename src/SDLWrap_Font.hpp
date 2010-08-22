#ifndef _SDLWRAP_FONT_H_
#define _SDLWRAP_FONT_H_

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include "ErrorHandler.hpp"

namespace SDLWrap {

class Font {
    public:
        /* This exception is thrown when a font could not be loaded for some reason, either because it wasn't a font or
         * the path to the TTF file is invalid. It is also thrown in the case that the TTF system could not be loaded.
         */
        class TTFError {};

        /* Typical constructor that opens a TTF font file using TTFFilePath and sets it to render at size FontSize.
         * Throws a TTFError in case the TTF system could not be loaded (Only happens when the first font is loaded or
         * if you try to load a font when the TTF system is not running, more generally as you can call Shutdown() then
         * load a font. Also keeps a refcount using FontCount.
         */
        Font(const std::string TTFFilePath, const int FontSize);

        /* Just frees the memory used by the Font and decrements FontCount. */
        ~Font();

        /* In case you want to shutdown the TTF system, just call this. It will only shutdown if there are no fonts in
         * memory, which it checks by comparing FontCount.
         */
        static void Shutdown();

    public:
        TTF_Font *me; // Publicize it so FontSurface can use it in it's rendering schemes.

    private:
        static int  FontCount;
        std::string FilePath;
};

};

#endif
