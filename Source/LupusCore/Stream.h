#pragma once

#include <vector>
#include <memory>
#include <future>
#include <cstdint>
#include <exception>
#include <functional>
#include <boost/noncopyable.hpp>

#include "Utility.h"
#include "Task.h"

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

        virtual Task<void> CopyToAsync(std::shared_ptr<Stream> destination) throw(std::invalid_argument);
        virtual Task<void> FlushAsync() throw(std::invalid_argument);
        virtual Task<int> ReadAsync(std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::invalid_argument);
        virtual Task<int> WriteAsync(const std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::invalid_argument);

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
        virtual int Read(std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::out_of_range) = 0;
        virtual int ReadByte() = 0;
        virtual int Write(const std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::out_of_range) = 0;
        virtual void WriteByte(uint8_t byte) = 0;
        virtual int64_t Seek(int64_t offset, SeekOrigin origin) throw(not_supported);
    };
}
