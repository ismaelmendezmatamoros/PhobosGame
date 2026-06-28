#pragma once

#include "common.hpp"
#include "window_base_interface.hpp"
#include "device_base_interface.hpp"
#include <GLFW/glfw3.h>
#include <queue>

namespace Phobos::Io::GLFW::Device {

    class KeyBoardDeviceGLFW : public Phobos::Io::Device::DeviceBaseInterface {
        public:
            KeyBoardDeviceGLFW(const std::string &deviceName, Phobos::Window::WindowBaseInterface &window);
            DeviceKeysStatus readStatus(const std::vector<KeyBoardKeyType> &filter = {}) override;
            static KeyBoardKeyType glfwKeyToPhobosKey(int key);

        protected:
            static void keyCallback(
                GLFWwindow* window,
                int key,
                int scancode,
                int action,
                int mods);

            static KeyStatus glfwKeyStatusToPhobos(int glfwKeyStatus);
            
            DeviceKeysStatus getCurrentState(std::queue<KeyInfo> &events);

            std::queue<KeyInfo> events;
            Phobos::Window::WindowBaseInterface &windowComponent;
    };
}