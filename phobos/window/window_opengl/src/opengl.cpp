#include "phobos/window/opengl/opengl.hpp"

#include <GL/gl.h>

namespace Phobos {
namespace Window {
namespace Opengl {

OpenGLContext::OpenGLContext() {
    // Constructor
}

OpenGLContext::~OpenGLContext() {
    // Destructor
}

void OpenGLContext::initialize() {
    // Initialize OpenGL context
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OpenGLContext::swapBuffers() {
    // Swap buffers (placeholder)
}

} // namespace opengl
} // namespace window
} // namespace phobos