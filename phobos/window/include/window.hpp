#pragma once

#ifndef USE_WINDOW_OPENGL
#define USE_WINDOW_OPENGL
#endif

#ifdef USE_WINDOW_OPENGL

#include "window_opengl.hpp"
#include "windows_definitions.hpp"

namespace Phobos::Window {
    using Window = Phobos::Window::OpenGL::WindowOpenGL;

}
#endif
