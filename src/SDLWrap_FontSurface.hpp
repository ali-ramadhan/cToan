/* SDLWrap_FontSurface.hpp
 *
 * Changelog:
 * 24/08/2010: - Added support for rendering text as blended.
 *             - Swithced from using pointers to Color objects to references. No need to construct a tmp SDL_Color in
 *               the render functions anymore, and still lets me used scoped_ptr's in the code.
 *             - Changed order of the constructor initializer (well, the one that people read) since it seems that the
 *               shared_ptr gets initialized first always, and changed the order to make it obvious to readers (me xD).
 *
 * 23/08/2010: - Stopped using a typedef for shared_ptr to Font, I'll leave header fully open.
 *             - Removed the useless empty destructor.
 *             - Changed constructor to initializer only, the constructor just assigned values anyways =/
 *             - Switched from using Color objects to pointer to Color objects, to easily use dynamically allocated
 *               objects.
 */

#ifndef _SDLWRAP_FONTSURFACE_H_
#define _SDLWRAP_FONTSURFACE_H_

#include <string>

#include <SDL/SDL.h>
#include <boost/shared_ptr.hpp>

#include "SDLWrap_Surface.hpp"
#include "SDLWrap_Font.hpp"
#include "SDLWrap_Color.hpp"

namespace SDLWrap {


/* The FontSurface class represents a Surface with some rendered text on it using a TTF font, and so therefore it makes
 * use of the Surface and Font classes. The reason for this class is that creating a surface with some text on it is a
 * common process so keeping it all nice and tidy in one class with it's related functions is a good idea.
 */
class FontSurface : public Surface
{
    public:
        // TODO: Should the RenderText* functions throw an exception if it fails to render or...?
        //       maybe depends on whether I render text every frame or only upon creation...
        /* The constructor takes a std::string so that it knows what text to render on the surface. It is of type
         * std::string even when SDL uses C style null terminated strings (and therefore internally in this class) but
         * I want to have more flexible access and usage over the string, and using a std::string doesn't really incure
         * that huge of an overhead so why not? We'll just use std::string::c_str() whenever we're dealing with SDL
         * calls.
         *
         * It also takes a boost shared_ptr to a Font object, which means it has to already exist.
         */
        FontSurface(const std::string Text, boost::shared_ptr<Font> TextFont, const Color &ColorOfText) :
            meFont(TextFont), SurfaceText(Text), ForegroundColor(ColorOfText) {}

        /* Renders a surface with text on it. The SurfaceText becomes the text, rendered in the font pointed to by
         * meFont and you can specify a color to render it in.
         *
         * Create an 8-bit palettized surface and render the given text at fast quality with the given font and color.
         * The pixel value of 0 is the colorkey, giving a transparent background when blitted. Pixel and colormap value
         * 1 is set to the text foreground color. This allows you to change the color without having to render the text
         * again. Palette index 0 is of course not drawn when blitted to another surface, since it is the colorkey, and
         * thus transparent, though its actual color is 255 minus each of the RGB components of the foreground color.
         * This is the fastest rendering speed of all the rendering modes. This results in no box around the text, but
         * the text is not as smooth. The resulting surface should blit faster than the Blended one. Use this mode for
         * FPS and other fast changing updating text displays.
         *
         * This and Blended/Shaded descriptions from: http://jcatki.no-ip.org/SDL_ttf/SDL_ttf_42.html#SEC42
         */
        void RenderTextSolid();

        /* Same as RenderTextSolid except that it renders it as blended, so it's much higher in quality and obviously
         * looks much better. The same link as above describes the Blended method in detail:
         *
         * Create a 32-bit ARGB surface and render the given text at high quality, using alpha blending to dither the
         * font with the given color. This results in a surface with alpha transparency, so you don't have a solid
         * colored box around the text. The text is antialiased. This will render slower than Solid, but in about the
         * same time as Shaded mode. The resulting surface will blit slower than if you had used Solid or Shaded. Use
         * this when you want high quality, and the text isn't changing too fast.
         */
        void RenderTextBlended();

        /* This function simply changes the color of the FontSurface. Well not really, it copies the provided NewFColor
         * to the instance's ForegroundColor. The FontSurface will have to be re-rendered for the changes to take place
         * though. Later it might not as it will record the rendered state but for now, you need to re-render.
         */
        void SetForegroundColor(Color &NewFColor);

    private:
        boost::shared_ptr<Font> meFont;
        std::string SurfaceText;
        Color ForegroundColor;
};

}

#endif
