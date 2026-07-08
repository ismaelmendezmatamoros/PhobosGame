#include "gpu_buffer_base_interface.hpp"

using namespace Phobos;

GPUBufferBaseInterface::GPUBufferBaseInterface(IdType bufferId, BufferType bufferType, std::size_t bufferSize) 
    : type{bufferType}
    , size{bufferSize}
    , id{bufferId}
    , inUse{false}
{
    readOnly = bufferType == BufferType::ShaderDataBufferReadOnly
            || bufferType == BufferType::PixelStorageReadBuffer
            || bufferType == BufferType::CopyReadBuffer;
}

bool Phobos::GPUBufferBaseInterface::isReadOnly() const
{
    return readOnly;
}

BufferType Phobos::GPUBufferBaseInterface::getType() const
{
    return type;
}

bool Phobos::GPUBufferBaseInterface::isAllocated() const
{
    return allocated;
}

IdType Phobos::GPUBufferBaseInterface::getId() const
{
    return id;
}

bool Phobos::GPUBufferBaseInterface::operator==(const GPUBufferBaseInterface &other) const
{
    return id == other.id;
}

bool Phobos::GPUBufferBaseInterface::operator<(const GPUBufferBaseInterface &other) const
{
    return id < other.id;;
}
