#pragma once

#include <vector>
#include <memory>
#include <cstdint>
#include <exception>
#include <functional>
#include <boost/noncopyable.hpp>

#include "Utility.h"

namespace Lupus {
    enum class SeekOrigin {
        Begin,
        Current,
        End
    };

    class LUPUS_API Stream : boost::noncopyable
    {
    public:

        virtual ~Stream() = default;

        virtual void CopyToAsync(std::shared_ptr<Stream> destination, std::function<void(std::exception_ptr, Stream*)> callback) NOEXCEPT;
        virtual void FlushAsync(std::function<void(std::exception_ptr, Stream*)> callback) NOEXCEPT;
        virtual void ReadAsync(std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size, std::function<void(std::exception_ptr, Stream*, int32_t)> callback) NOEXCEPT;
        virtual void WriteAsync(const std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size, std::function<void(std::exception_ptr, Stream*, int32_t)> callback) NOEXCEPT;

        virtual bool CanRead() const = 0;
        virtual bool CanWrite() const = 0;
        virtual bool CanSeek() const = 0;

        virtual void Close() = 0;
        virtual void CopyTo(std::shared_ptr<Stream> destination) throw(null_pointer, not_supported);
        virtual void Flush() throw(not_supported);
        virtual int64_t Length() const = 0;
        virtual void Length(int64_t) throw(not_supported, std::out_of_range);
        virtual int64_t Position() const = 0;
        virtual void Position(int64_t) throw(not_supported, std::out_of_range);
        virtual int32_t Read(std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size) throw(std::out_of_range) = 0;
        virtual int32_t ReadByte() = 0;
        virtual int32_t Write(const std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size) throw(std::out_of_range) = 0;
        virtual void WriteByte(uint8_t byte) = 0;
        virtual int64_t Seek(int64_t offset, SeekOrigin origin) throw(not_supported);
    };
}
