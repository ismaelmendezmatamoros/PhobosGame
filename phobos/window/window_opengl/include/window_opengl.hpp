#pragma once

#include "window_base_interface.hpp"
#include "common.hpp"

#include <GL/gl.h>

namespace Phobos {
namespace Window {
namespace OpenGL {

    class WindowOpenGL : public WindowBaseInterface {
    public:
        WindowOpenGL(Window::WindowConfiguration config = Window::WindowConfiguration{});
        ~WindowOpenGL() override = default;

        void show() override;
        void hide() override;
        
        void close() override;
        bool getFullScreen() const override;
        bool setFullScreen() override;

        Resolution getResolution() const override;
        void setResolution(const Resolution &newResolution) override;

        void refresh() override;

        std::string formatHeader() const override;

        private:
         static constexpr std::string logHeader{"Window"};
    };

} // namespace Opengl
} // namespace Window
} // namespace Phobos