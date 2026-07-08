#pragma once

#include <span>
#include "common.hpp"

namespace Phobos {

    enum class BufferType : int {
        ArrayBuffer,
        ShaderDataBuffer,
        ShaderDataBufferReadOnly,
        ElementArrayBuffer,
        TextureBuffer,
        PixelStorageReadBuffer,
        PixelStorageWriteBuffer,
        QueryBuffer,
        CopyReadBuffer,
        CopyWriteBuffer
    };

    class GPUBufferBaseInterface {
      public:
      GPUBufferBaseInterface(IdType bufferId, BufferType type, std::size_t size);
      virtual ~GPUBufferBaseInterface() = default;

      bool isReadOnly() const;
      BufferType getType() const;
      virtual void write(std::span<std::byte> data) = 0;
      virtual const std::span<std::byte> read(std::size_t pos) const = 0;
      virtual void freeBuffer() = 0;
      virtual void useBuffer(bool use) = 0;
      bool isAllocated() const;
      IdType getId() const;
      bool operator==(const GPUBufferBaseInterface &other) const;
      bool operator<(const GPUBufferBaseInterface &other) const;

      protected:
      bool readOnly;
      bool allocated;
      std::size_t size;
      BufferType type;
      IdType id;
      bool inUse;
    };
}