#pragma once

#include <GL/gl.h>

namespace phobos {
namespace window {
namespace opengl {

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