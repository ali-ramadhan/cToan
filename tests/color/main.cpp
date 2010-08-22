#include "SDLWrap_SDLEngine.hpp"
#include "SDLWrap_Color.hpp"
#include <iostream>
using namespace SDLWrap;

int
main()
{
    SDLEngine engine(SDLEngine::EVERYTHING);
    Color nothing;
    Color random(122, 33, 23);
    std::cout << "sizeof(SDLEngine): " << sizeof(SDLEngine) << "\nsizeof(Color) " << sizeof(Color) << '\n';
    return 5;
}
