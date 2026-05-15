#pragma once

#include "window_base_interface.hpp"
#include "common.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>

namespace Phobos {
namespace Window {
namespace OpenGL {

    class WindowOpenGL : public WindowBaseInterface {
    public:
        WindowOpenGL(Window::WindowConfiguration config = Window::WindowConfiguration{});
        ~WindowOpenGL() override;

        void show() override;
        void hide() override;
        
        void close() override;
        bool getFullScreen() const override;
        bool setFullScreen() override;

        Resolution getResolution() const override;
        void setResolution(const Resolution &newResolution) override;

        void execute() override;
        void initialize() override;

        void setClearColor(const glm::vec4 &color) override;

        void refresh() override;
        
        void onWindowResizeCallback(GLFWwindow *window, int width, int height); 
        
        private:
         static constexpr std::string componentNameConst{"Window"};
         GLFWwindow *window;
    };

} // namespace Opengl
} // namespace Window
} // namespace Phobos