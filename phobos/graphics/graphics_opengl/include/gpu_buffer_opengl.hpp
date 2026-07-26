#pragma once

#include "gpu_buffer_base_interface.hpp"

#include "include_opengl.hpp"

namespace Phobos::Graphics::OpenGL {
    class GPUBufferOpenGL : public Phobos::GPUBufferBaseInterface {

    public:
    GPUBufferOpenGL(IdType bufferId, BufferType bufferType, std::size_t bufferSize);
    ~GPUBufferOpenGL();
    
    const std::vector<std::byte> read(std::size_t pos, std::size_t size) const override;
    void useBuffer(bool use) override;
    void freeBuffer() override;

    protected:
    void writeInternal(const std::span<const std::byte> &data, std::size_t pos = 0) override;
    static GLenum bufferTypeToGLenum(BufferType);
    
    GLuint glBufferHandler;
    GLenum glTargetBuffer;

    };

}