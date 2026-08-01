#include "graphics_base_interface.hpp"

Phobos::Graphics::GraphicsBaseInterface::GraphicsBaseInterface()
    : Phobos::EngineComponent{graphicsNameStr}
{
}

ShaderManager& Phobos::Graphics::GraphicsBaseInterface::getShaderManager() {
    return shaderManager;
}
