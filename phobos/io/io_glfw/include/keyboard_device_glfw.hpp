#pragma once

#include "common.hpp"
#include "window.hpp"
#include "device_base_interface.hpp"
#include <queue>

namespace Phobos::Io::GLFW::Device {

    class KeyBoardDeviceGLFW : public Phobos::Io::Device::DeviceBaseInterface {
        public:
            KeyBoardDeviceGLFW(const std::string &deviceName, Phobos::Window::Window &window);
            std::map<KeyBoardKeyType, KeyStatus> readStatus(const std::vector<KeyBoardKeyType> &filter = {}) override;
            static KeyBoardKeyType glfwKeyToPhobosKey(int key);

        protected:
            static void keyCallback(
                GLFWwindow* window,
                int key,
                int scancode,
                int action,
                int mods);

            static KeyStatus glfwKeyStatusToPhobos(int glfwKeyStatus);
            
            std::map<KeyBoardKeyType, KeyStatus> getCurrentState(std::queue<KeyInfo> &events);

            std::queue<KeyInfo> events;
            Phobos::Window::Window &windowComponent;
    };
}