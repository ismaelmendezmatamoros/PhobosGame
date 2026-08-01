#pragma once

#include <glm/glm.hpp>
#include "graphics_common.hpp"
#include <filesystem>

namespace Phobos::Graphics {
    static inline std::filesystem::path shaderCommonSourceFolders{"shaders"};
}

#ifndef USE_GRAPHICS_OPENGL
#define USE_GRAPHICS_OPENGL
#endif

#ifdef USE_GRAPHICS_OPENGL
#include "graphics_opengl.hpp"


namespace Phobos::Graphics {
    using Graphics = OpenGL::GraphicsOpenGL;
    using ShaderStage = OpenGL::ShaderStageOpenGl;
    using GPUBuffer = OpenGL::GPUBufferOpenGL;
    using GPUMemoryManager = OpenGL::GPUMemoryManagerOpenGL;

    static inline std::filesystem::path shaderSourceFolders{shaderCommonSourceFolders.append("opengl")};
}
#endif
