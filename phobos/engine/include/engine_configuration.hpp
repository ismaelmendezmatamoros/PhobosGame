#pragma once

#include "windows_definitions.hpp"
#include "io.hpp"

using namespace Phobos;

namespace Phobos {

    enum class InitializeComponentEnum : int {
        Window = 1,
        Graphics = 2,
        Sound = 4,
        Io = 8,
        All = 16
    };
    using InitializeComponentEnumType = int;

    struct EngineConfiguration {
        InitializeComponentEnumType initializeComponents{
                static_cast<InitializeComponentEnumType>(InitializeComponentEnum::All)};
        Window::WindowConfiguration windowConfiguration;
        Io::IoConfiguration ioConfiguration;
    };
    
}