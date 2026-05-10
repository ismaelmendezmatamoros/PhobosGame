#pragma once

#include <string>

namespace Phobos::Window {

    struct Resolution {
        int width;
        int height;
    };

    struct WindowConfiguration {
        Resolution resolution{800, 600};
        bool fullScreen{false};
        std::string title;
    };
}