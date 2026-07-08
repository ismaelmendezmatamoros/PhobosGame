#include "gpu_memory_manager_base_interface.hpp"

GPUBufferBaseInterface *Phobos::GPUMemoryManagerBaseInterface::getBuffer(const IdType id)
{    
    if (auto it = buffers.find(id); it != buffers.end())
        return it->second.get();
    return nullptr;
}

bool Phobos::GPUMemoryManagerBaseInterface::deleteBuffer(const IdType id)
{
    return buffers.erase(id);
}

GPUBufferBaseInterface *Phobos::GPUMemoryManagerBaseInterface::createBuffer(IdType bufferId, BufferType type, std::size_t size)
{
    auto result = buffers.emplace(bufferId, std::move(createBufferInstance(bufferId, type, size)));
    if (result.second)
        return result.first->second.get();
    return nullptr;
}
