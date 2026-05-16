
#include "keyboard_device_glfw.hpp"

using namespace Phobos::Io::GLFW::Device;

KeyBoardDeviceGLFW::KeyBoardDeviceGLFW(const std::string &deviceName)
        : Phobos::Io::Device::DeviceBaseInterface{DeviceType::keyboard, deviceName} {

}

std::vector<int> KeyBoardDeviceGLFW::readStatus(const std::vector<int> &filter) {
    return {};
}