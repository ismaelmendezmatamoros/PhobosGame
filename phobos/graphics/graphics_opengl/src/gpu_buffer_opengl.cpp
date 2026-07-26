#include "gpu_buffer_opengl.hpp"

GLenum Phobos::Graphics::OpenGL::GPUBufferOpenGL::bufferTypeToGLenum(BufferType type)
{
    switch (type)
    {
        /*
        GL_ARRAY_BUFFER	Vertex attributes
GL_ATOMIC_COUNTER_BUFFER	Atomic counter storage
GL_COPY_READ_BUFFER	Buffer copy source
GL_COPY_WRITE_BUFFER	Buffer copy destination
GL_DISPATCH_INDIRECT_BUFFER	Indirect compute dispatch commands
GL_DRAW_INDIRECT_BUFFER	Indirect command arguments
GL_ELEMENT_ARRAY_BUFFER	Vertex array indices
GL_PIXEL_PACK_BUFFER	Pixel read target
GL_PIXEL_UNPACK_BUFFER	Texture data source
GL_QUERY_BUFFER	Query result buffer
GL_SHADER_STORAGE_BUFFER	Read-write storage for shaders
GL_TEXTURE_BUFFER	Texture data buffer
GL_TRANSFORM_FEEDBACK_BUFFER	Transform feedback buffer
GL_UNIFORM_BUFFER	Uniform block storage
        */
    case BufferType::ArrayBuffer:  !!!!comprobar que todos los tipos tengan sentido. revisar los read only
        return GL_ARRAY_BUFFER;
    case BufferType::CopyReadBuffer:
        return GL_COPY_READ_BUFFER;
    case BufferType::CopyWriteBuffer:
        return GL_COPY_WRITE_BUFFER;
    case BufferType::ElementArrayBuffer:
        return GL_ELEMENT_ARRAY_BUFFER;
    case BufferType::PixelStorageReadBuffer:
        return GL_PIXEL_PACK_BUFFER;
    case BufferType::PixelStorageWriteBuffer:
        return GL_ARRAY_BUFFER;
    case BufferType::QueryBuffer:
        return GL_QUERY_BUFFER;
    case BufferType::ShaderDataBuffer:
        return GL_SHADER_STORAGE_BUFFER;
    case BufferType::ShaderDataBufferReadOnly:
        return GL_SHADER_STORAGE_BUFFER;
    case BufferType::TextureBuffer:
        return GL_TEXTURE_BUFFER;
    default:
        return -1;
    };
    return GLenum();
}

Phobos::Graphics::OpenGL::GPUBufferOpenGL::GPUBufferOpenGL(IdType bufferId, BufferType bufferType, std::size_t bufferSize)
    : GPUBufferBaseInterface{bufferId, bufferType, bufferSize}
    , glTargetBuffer{bufferTypeToGLenum(bufferType)}
{
    glCreateBuffers(1, &glBufferHandler);
    glNamedBufferStorage(
        glBufferHandler,
        bufferSize,
        nullptr,
        GL_DYNAMIC_STORAGE_BIT
    );!!!!!!!vas por aqqui
    mira a ver si tiene mas cuenta usar un mapeo de buffer a puntero para ller yh escribir que usar
    glNamedBufferStorage. de todas formas esto funciona.
lo siguiente que tienes que implementart son los shaders!!!!

}

Phobos::Graphics::OpenGL::GPUBufferOpenGL::~GPUBufferOpenGL()
{
    freeBuffer();
}

void Phobos::Graphics::OpenGL::GPUBufferOpenGL::writeInternal(const std::span<const std::byte> &data, std::size_t pos)
{
    glNamedBufferSubData(
        glBufferHandler,
        pos,
        data.size(),
        data.data());
}

const std::vector<std::byte> Phobos::Graphics::OpenGL::GPUBufferOpenGL::read(std::size_t pos, std::size_t size) const
{
    std::vector<std::byte> data(size);
    glGetNamedBufferSubData(
        glBufferHandler,
        pos,
        size,
        data.data());
    return data;
}

void Phobos::Graphics::OpenGL::GPUBufferOpenGL::useBuffer(bool use)
{

}

void Phobos::Graphics::OpenGL::GPUBufferOpenGL::freeBuffer()
{

}
