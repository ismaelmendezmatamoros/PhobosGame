#pragma once

#include "window.hpp"
#include "io.hpp"

using namespace Phobos;

namespace Phobos::Engine {

    enum class InitializeComponentEnum : int {
        Window = 1,
        Graphics = 2,
        Sound = 4,
        Io = 8,
        All = 16
    };
    using InitializeComponentEnumType = int;

    struct Configuration {
        InitializeComponentEnumType initializeComponents{
                static_cast<InitializeComponentEnumType>(InitializeComponentEnum::All)};
        Window::WindowConfiguration windowConfiguration;
        Io::IoConfiguration ioConfiguration;
    };
    
}