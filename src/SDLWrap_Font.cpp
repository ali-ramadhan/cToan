#include "SDLWrap_Font.hpp"

namespace SDLWrap {

int Font::FontCount = 0;

Font::Font(const std::string FilePath, const int FontSize)
try {
    this->me = NULL;

    if (!TTF_WasInit() && TTF_Init() == -1)
        throw TTFError();

    if ( (this->me = TTF_OpenFont(FFilePath.c_str(), FontSize)) == NULL )
        throw TTFError();

    FontCount++;
}
catch (TTFError)
{
    std::string Error = "Font::Font(char*) constructor threw a TTFError! ";
    if (TTF_WasInit()) {
        Error += "The TTF core was initialized.\n";
    } else {
        Error += "The TTF core was not initialized.\n";
    }
    ErrorHandler::OutputError(ErrorHandler::FATAL_CONSTRUCTOR_ERROR, Error);
}

Font::~Font()
{
    TTF_CloseFont(this->me);
    FontCount--;
}

void
Font::Shutdown()
{
    if (FontCount == 0) {
        TTF_Quit();
    } else {
        // I dunno, do something useful <_<
        // Maybe leave it to the ErrorHandler to report the error somehow?
    }
}

};
