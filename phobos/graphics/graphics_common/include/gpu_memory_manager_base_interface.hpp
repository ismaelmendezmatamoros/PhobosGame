#pragma once

#include "gpu_buffer_base_interface.hpp"
#include <map>
#include <memory>

namespace Phobos {
    class GPUMemoryManagerBaseInterface {
    
    public:
    virtual ~GPUMemoryManagerBaseInterface() = default;
    GPUBufferBaseInterface* getBuffer(const IdType id);
    bool deleteBuffer(const IdType id);
    GPUBufferBaseInterface* createBuffer(IdType bufferId, BufferType type, std::size_t size);

    protected:
    virtual std::unique_ptr<GPUBufferBaseInterface> createBufferInstance(IdType bufferId, BufferType type, std::size_t size) = 0;
    std::map<IdType, std::unique_ptr<GPUBufferBaseInterface>> buffers;
    //std::set<>

};
}