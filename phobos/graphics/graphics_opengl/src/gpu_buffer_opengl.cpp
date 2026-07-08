#include "gpu_buffer_opengl.hpp"

Phobos::Graphics::OpenGL::GPUBufferOpenGL::GPUBufferOpenGL(IdType bufferId, BufferType bufferType, std::size_t bufferSize)
    : GPUBufferBaseInterface{bufferId, bufferType, bufferSize}
{
    glCreateBuffers(1, &glBufferHandler);


}

Phobos::Graphics::OpenGL::GPUBufferOpenGL::~GPUBufferOpenGL()
{
    freeBuffer();
}

void Phobos::Graphics::OpenGL::GPUBufferOpenGL::write(std::span<std::byte> data)
{
}

const std::span<std::byte> Phobos::Graphics::OpenGL::GPUBufferOpenGL::read(std::size_t pos) const
{
    return std::span<std::byte>();
}

void Phobos::Graphics::OpenGL::GPUBufferOpenGL::useBuffer(bool use)
{

}

void Phobos::Graphics::OpenGL::GPUBufferOpenGL::freeBuffer()
{
}
