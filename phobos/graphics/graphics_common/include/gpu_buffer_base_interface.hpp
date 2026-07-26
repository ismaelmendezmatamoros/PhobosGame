#pragma once

#include <span>
#include <concepts>
#include "common.hpp"

namespace Phobos {

    template<typename T>
    concept SpanCompatible =
        requires(T& value)
        {
            std::span{value};
        };

    enum class BufferType : int {
        ArrayBuffer,
        CopyReadBuffer,
        CopyWriteBuffer,
        ElementArrayBuffer,
        PixelStorageReadBuffer,
        PixelStorageWriteBuffer,
        QueryBuffer,
        ShaderDataBuffer,
        ShaderDataBufferReadOnly,
        TextureBuffer
    };

    class GPUBufferBaseInterface {
      public:
      GPUBufferBaseInterface(IdType bufferId, BufferType type, std::size_t size);
      virtual ~GPUBufferBaseInterface() = default;

      bool isReadOnly() const;
      BufferType getType() const;
    
      template<SpanCompatible T>
      inline void write(const T &data, std::size_t pos);
      //virtual void writeInternal(const std::span<const std::byte> &data, std::size_t pos) = 0;
      virtual const std::vector<std::byte> read(std::size_t pos, std::size_t size) const = 0;
      virtual void freeBuffer() = 0;
      virtual void useBuffer(bool use) = 0;
      bool isAllocated() const;
      IdType getId() const;
      bool operator==(const GPUBufferBaseInterface &other) const;
      bool operator<(const GPUBufferBaseInterface &other) const;

      protected:
      virtual void writeInternal(const std::span<const std::byte> &data, std::size_t pos = 0) = 0;
      bool readOnly;
      bool allocated;
      std::size_t size;
      BufferType type;
      IdType id;
      bool inUse;
    };


    
    template<SpanCompatible T>
    inline void GPUBufferBaseInterface::write(const T &data, std::size_t pos)
    {
        writeInternal(std::as_bytes(std::span{data}), pos);
    }
}