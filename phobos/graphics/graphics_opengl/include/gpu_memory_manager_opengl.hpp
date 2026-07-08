#pragma once

#include "gpu_memory_manager_base_interface.hpp"
#include "gpu_buffer_opengl.hpp"

namespace Phobos::Graphics::OpenGL {
    class GPUMemoryManagerOpenGL : public Phobos::GPUMemoryManagerBaseInterface {
    protected:
    std::unique_ptr<GPUBufferBaseInterface> createBufferInstance(IdType bufferId, BufferType type, std::size_t size) override;
    };
}