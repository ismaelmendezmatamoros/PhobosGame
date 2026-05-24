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

            bool insertStatus(std::map<KeyBoardKeyType, KeyStatus> &&status) override;

        protected:
            static void keyCallback(
                GLFWwindow* window,
                int key,
                int scancode,
                int action,
                int mods);

            std::optional<std::map<KeyBoardKeyType, KeyStatus>> previousKbState;
            //std::map<KeyBoardKeyType, KeyStatus> *previousKbState{nullptr};
            Phobos::Window::Window &windowComponent;
    };
}