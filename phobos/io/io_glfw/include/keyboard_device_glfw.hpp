#pragma once

#include "common.hpp"
#include "device_base_interface.hpp"

namespace Phobos::Io::GLFW::Device {

    class KeyBoardDeviceGLFW : public Phobos::Io::Device::DeviceBaseInterface {
        public:
            KeyBoardDeviceGLFW(const std::string &deviceName);
            std::vector<int> readStatus(const std::vector<int> &filter = {}) override;
    };
}