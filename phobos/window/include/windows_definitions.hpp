#pragma once

#include <string>

namespace Phobos {
namespace Window {

    struct Resolution {
        int width;
        int height;
    };

    struct WindowConfiguration {
        Resolution resolution{800, 600};
        bool fullScreen{false};
        std::string title;
        bool resizeable{true};
        int bpp{32};
    };

}
}