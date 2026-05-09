#pragma once

#include "phobos/window/window_base_interface.hpp"
#include "phobos/common/common.hpp"

#include <GL/gl.h>

namespace Phobos {
namespace Window {
namespace OpenGL {

    class WindowOpenGL : public WindowBaseInterface {
    public:
        WindowOpenGL();
        ~WindowOpenGL() override = default;

        void show() override;
        void hide() override;
        
        void close() override;
        bool getFullScreen() const override;
        bool setFullScreen() override;

        Resolution getResolution() const override;
        void setResolution(const Resolution &newResolution) override;

        void refresh() override;
    };

} // namespace Opengl
} // namespace Window
} // namespace Phobos