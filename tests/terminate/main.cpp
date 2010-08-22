#include "SDLWrap_SDLEngine.hpp"

using namespace SDLWrap;

int main()
{
    SDLEngine *engine = new SDLEngine(SDLEngine::VIDEO);
    std::cout << engine->WasInit(0) << '\n';
    return 0;
}
