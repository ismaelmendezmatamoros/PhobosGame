#pragma once

#include "io_base_interface.hpp"

namespace Phobos::Io::GLFW {
    // GLFW Input/Output utilities
    class IoGLFW : public Phobos::Io::IoBaseInterface {
    public:

        IoGLFW(
                Phobos::Window::Window &window,
                const IoConfiguration &config);
        void initialize() override;
        void execute() override;
        void readInput() override;
    private:
        static constexpr std::string componentNameConst{"Io"};
    };
}
