#pragma once

#include <glm/glm.hpp>
#include "graphics_common.hpp"

#ifndef USE_GRAPHICS_OPENGL
#define USE_GRAPHICS_OPENGL
#endif

#ifdef USE_GRAPHICS_OPENGL
#include "graphics_opengl.hpp"

namespace Phobos::Graphics {
    using Graphics = OpenGL::GraphicsOpenGL;
}
#endif
