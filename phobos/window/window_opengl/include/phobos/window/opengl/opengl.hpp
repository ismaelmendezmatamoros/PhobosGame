#pragma once

#include <GL/gl.h>

namespace Phobos {
namespace Window {
namespace Opengl {

class OpenGLContext {
public:
    OpenGLContext();
    ~OpenGLContext();

    void initialize();
    void swapBuffers();
};

} // namespace opengl
} // namespace window
} // namespace phobos