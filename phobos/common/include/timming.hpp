#pragma once

#include <chrono>

namespace Phobos::Timming {

    static const auto startTime = std::chrono::system_clock::now();
    static const auto startTimeInMs = std::chrono::floor<std::chrono::milliseconds>(
        startTime.time_since_epoch());
    using TimeStampType = decltype(startTime);
    using MillisecondsType = std::chrono::milliseconds;

    MillisecondsType getStartupTimeInMs();
}