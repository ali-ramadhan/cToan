#include <boost/timer.hpp>
#include "Logger.hpp"

int
main()
{
    boost::timer normalStrings;
    for (int i = 0; i < 1000000; i++) {
        if (false) { Logger::Log(Logger::CONSTRUCTOR, "DEBUG: Something has failed, oh shit <_<\n"); }
    }
    std::cout << normalStrings.elapsed();
    return 0;
}
