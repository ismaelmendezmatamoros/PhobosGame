
#include "timming.hpp"

using namespace Phobos::Timming;

MillisecondsType Phobos::Timming::getStartupTimeInMs()
{
    return std::chrono::floor<std::chrono::milliseconds>(startTime.time_since_epoch());
}
