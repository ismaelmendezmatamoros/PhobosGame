#include "io_glfw.hpp"

using namespace Phobos::Io::GLFW;

IoGLFW::IoGLFW(Phobos::Window::Window &window, const IoConfiguration &config)
    : IoBaseInterface{componentNameConst, config, window} {}

void IoGLFW::initialize() {
    bool initializeAll = configuration.InitializeDeviceMask && static_cast<int>(InitializeDeviceMaskType::All);
    bool initializeKeyBoard = configuration.InitializeDeviceMask && static_cast<int>(InitializeDeviceMaskType::Keyboard);
    if (initializeAll || initializeKeyBoard) {
        keyboard = createKeyboardDevice("KeyBoard_0");
    }
}

Device::KeyBoardDeviceGLFW *IoGLFW::createKeyboardDevice(const std::string &deviceName) {
    auto keyBoard = std::make_unique<Device::KeyBoardDeviceGLFW>(deviceName, std::ref(windowComponent));
    auto id = keyBoard->getId();
    auto result = devicesMap.emplace(id, std::move(keyBoard));
    Device::KeyBoardDeviceGLFW *createdKb = nullptr;
    if (!result.second)
        return nullptr;
    return dynamic_cast<Device::KeyBoardDeviceGLFW*>( result.first->second.get());
}

void IoGLFW::execute() {
    readInput();
}

void IoGLFW::readInput() {
    auto kbStatus = keyboard->readStatus();
    if (kbStatus.contains(KeyBoardKeyType::Key_W) && kbStatus[KeyBoardKeyType::Key_W] == KeyStatus::Pressed) {
        auto color =  windowComponent.getClearColor();
        color.x +=0.1;
        color.y += 0.05; 
        windowComponent.setClearColor(color);
    }
    if (kbStatus.contains(KeyBoardKeyType::Key_S) && kbStatus[KeyBoardKeyType::Key_S] == KeyStatus::Released) {
        auto color =  windowComponent.getClearColor();
        color.x -=0.1;
        color.y -= 0.05; 
        windowComponent.setClearColor(color);
    }

}






