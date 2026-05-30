
#include "keyboard_device_glfw.hpp"
#include <GLFW/glfw3.h>

using namespace Phobos::Io::GLFW::Device;


Phobos::Io::KeyStatus KeyBoardDeviceGLFW::glfwKeyStatusToPhobos(int glfwKeyStatus) {
    switch (glfwKeyStatus) {
  
        case GLFW_PRESS: return KeyStatus::Pressed;
        case GLFW_RELEASE: return KeyStatus::Released;
        case GLFW_REPEAT: return KeyStatus::StillPressed;
        
        default:
            return KeyStatus::Unknown;

    }

}

void KeyBoardDeviceGLFW::keyCallback(
                                    GLFWwindow* window,
                                    int key,
                                    int scancode,
                                    int action,
                                    int mods) {

    auto self = static_cast<KeyBoardDeviceGLFW*>(glfwGetWindowUserPointer(window));
    auto nativeWindow = static_cast<GLFWwindow*>(self->windowComponent.getNativeWindow());
    KeyInfo current;

    //for (int i = 0; i < GLFW_KEY_LAST; ++i) {
    auto phobosKey = glfwKeyToPhobosKey(key);
    if (phobosKey == KeyBoardKeyType::Unknown)
        return;
    
    auto keyStatus = glfwKeyStatusToPhobos(action);
    if (keyStatus == KeyStatus::Unknown)
        return;
    
    current.keyId = static_cast<KeyBoardKeyType>(phobosKey);
    current.status = static_cast<KeyStatus>(keyStatus);
    self->events.push(std::move(current));
}

KeyBoardDeviceGLFW::KeyBoardDeviceGLFW(const std::string &deviceName,  Phobos::Window::Window &window)
        : Phobos::Io::Device::DeviceBaseInterface{DeviceType::keyboard, deviceName}
        , windowComponent{window} {

    GLFWwindow* ptr = static_cast<GLFWwindow*>(windowComponent.getNativeWindow());
    glfwSetWindowUserPointer(ptr, this);
    glfwSetKeyCallback(
            ptr,
            &KeyBoardDeviceGLFW::keyCallback);
    glfwSetWindowUserPointer(ptr, this);
}

std::map<Phobos::Io::KeyBoardKeyType, Phobos::Io::KeyStatus> KeyBoardDeviceGLFW::readStatus(const std::vector<KeyBoardKeyType> &filter) {
    glfwPollEvents();
    if (events.empty())
        return {};

    return getCurrentState(events);
}

std::map<Phobos::Io::KeyBoardKeyType, Phobos::Io::KeyStatus> KeyBoardDeviceGLFW::getCurrentState(
        std::queue<KeyInfo> &events) {
    std::map<KeyBoardKeyType, KeyStatus> current;
    while (!events.empty()) {
        auto event = std::move(events.front());
        events.pop();
        current.insert_or_assign(event.keyId, event.status);
    }

    return current;
}

Phobos::Io::KeyBoardKeyType KeyBoardDeviceGLFW::glfwKeyToPhobosKey(int key) {
    using namespace Phobos::Io;

    switch (key) {
        case GLFW_KEY_A: return KeyBoardKeyType::Key_A;
        case GLFW_KEY_B: return KeyBoardKeyType::Key_B;
        case GLFW_KEY_C: return KeyBoardKeyType::Key_C;
        case GLFW_KEY_D: return KeyBoardKeyType::Key_D;
        case GLFW_KEY_E: return KeyBoardKeyType::Key_E;
        case GLFW_KEY_F: return KeyBoardKeyType::Key_F;
        case GLFW_KEY_G: return KeyBoardKeyType::Key_G;
        case GLFW_KEY_H: return KeyBoardKeyType::Key_H;
        case GLFW_KEY_I: return KeyBoardKeyType::Key_I;
        case GLFW_KEY_J: return KeyBoardKeyType::Key_J;
        case GLFW_KEY_K: return KeyBoardKeyType::Key_K;
        case GLFW_KEY_L: return KeyBoardKeyType::Key_L;
        case GLFW_KEY_M: return KeyBoardKeyType::Key_M;
        case GLFW_KEY_N: return KeyBoardKeyType::Key_N;
        case GLFW_KEY_O: return KeyBoardKeyType::Key_O;
        case GLFW_KEY_P: return KeyBoardKeyType::Key_P;
        case GLFW_KEY_Q: return KeyBoardKeyType::Key_Q;
        case GLFW_KEY_R: return KeyBoardKeyType::Key_R;
        case GLFW_KEY_S: return KeyBoardKeyType::Key_S;
        case GLFW_KEY_T: return KeyBoardKeyType::Key_T;
        case GLFW_KEY_U: return KeyBoardKeyType::Key_U;
        case GLFW_KEY_V: return KeyBoardKeyType::Key_V;
        case GLFW_KEY_W: return KeyBoardKeyType::Key_W;
        case GLFW_KEY_X: return KeyBoardKeyType::Key_X;
        case GLFW_KEY_Y: return KeyBoardKeyType::Key_Y;
        case GLFW_KEY_Z: return KeyBoardKeyType::Key_Z;
        case GLFW_KEY_LEFT_SHIFT: return KeyBoardKeyType::Key_LSHIFT;
        case GLFW_KEY_RIGHT_SHIFT: return KeyBoardKeyType::Key_RSHIFT; 
        case GLFW_KEY_LEFT_CONTROL: return KeyBoardKeyType::Key_LCTRL;
        case GLFW_KEY_LEFT_ALT: return KeyBoardKeyType::Key_ALT;
        case GLFW_KEY_RIGHT_CONTROL: return KeyBoardKeyType::Key_RCTRL;
        case GLFW_KEY_RIGHT_ALT: return KeyBoardKeyType::Key_ALTGR;
        case GLFW_KEY_SPACE: return KeyBoardKeyType::Key_SPACE;
        case GLFW_KEY_APOSTROPHE:  return KeyBoardKeyType::Key_APOSTROPHE;
        case GLFW_KEY_COMMA: return KeyBoardKeyType::Key_COMMA;
        case GLFW_KEY_MINUS: return KeyBoardKeyType::Key_MINUS;
        case GLFW_KEY_PERIOD: return KeyBoardKeyType::Key_PERIOD;
        case GLFW_KEY_SLASH: return KeyBoardKeyType::Key_SLASH;
        default:
            return KeyBoardKeyType::Unknown;
    }
    
}


