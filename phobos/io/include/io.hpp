#pragma once

#define USE_IO_GLFW
#ifdef USE_IO_GLFW

#include "io_glfw.hpp"

namespace Phobos::Io {
    using Io = Phobos::Io::GLFW::IoGLFW;

}
#endif
