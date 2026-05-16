#pragma once

#include "io_base_interface.hpp"
#include "keyboard_device_glfw.hpp"

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

        Device::KeyBoardDeviceGLFW *createKeyboardDevice(const std::string &deviceName);

    private:
        static constexpr std::string componentNameConst{"Io"};
        Device::KeyBoardDeviceGLFW *keyboard;
    };
}
