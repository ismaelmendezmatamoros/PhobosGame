#include "gpu_memory_manager_opengl.hpp"

std::unique_ptr<GPUBufferBaseInterface> Phobos::Graphics::OpenGL::GPUMemoryManagerOpenGL::createBufferInstance(IdType bufferId, BufferType type, std::size_t size)
{
    return std::make_unique<GPUBufferOpenGL>(bufferId, type, size);
}
