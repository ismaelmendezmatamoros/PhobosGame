#include "graphics_base_interface.hpp"

Phobos::Graphics::GraphicsBaseInterface::GraphicsBaseInterface()
    : Phobos::EngineComponent{graphicsNameStr}
{
}

GPUMemoryManagerBaseInterface *Phobos::Graphics::GraphicsBaseInterface::getGPUMemoryManager()
{
    return gpuMemoryManager.get();
}
