#pragma once

#include "gpu_buffer_base_interface.hpp"

#include "include_opengl.hpp"

namespace Phobos::Graphics::OpenGL {
    class GPUBufferOpenGL : public Phobos::GPUBufferBaseInterface {

    public:
    GPUBufferOpenGL(IdType bufferId, BufferType bufferType, std::size_t bufferSize);
    ~GPUBufferOpenGL();
    void write(std::span<std::byte> data) override;
    const std::span<std::byte> read(std::size_t pos) const override;
    void useBuffer(bool use) override;
    void freeBuffer() override;

    protected:
    GLuint glBufferHandler;

    };

}