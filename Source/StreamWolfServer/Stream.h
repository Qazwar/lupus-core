#pragma once

#include <vector>
#include <memory>
#include <cstdint>
#include <exception>
#include <functional>
#include <boost/noncopyable.hpp>

#include "Utility.h"

namespace StreamWolf {
    enum class SeekOrigin {
        Begin,
        Current,
        End
    };

    class ReadStream : public boost::noncopyable
    {
    public:

        virtual ~ReadStream() = default;

        virtual void ReadAsync(std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size, std::function<void(std::exception_ptr, int32_t)> callback) NOEXCEPT = 0;

        virtual void Close() = 0;
        virtual void Flush() { };
        virtual int64_t Length() const = 0;
        virtual int64_t Position() const { return 0 };
        virtual void Position(int64_t) { };
        virtual int32_t Read(std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size) = 0;
        virtual int32_t ReadByte() = 0;
        virtual int64_t Seek(int64_t offset, SeekOrigin origin) { return 0 };
    };

    class WriteStream : public boost::noncopyable
    {
    public:

        virtual ~WriteStream() = default;

        virtual void WriteAsync(const std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size, std::function<void(std::exception_ptr, int32_t)> callback) NOEXCEPT = 0;

        virtual void Close() = 0;
        virtual int64_t Length() const = 0;
        virtual int64_t Position() const { return 0 };
        virtual void Position(int64_t) { };
        virtual int32_t Write(const std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size) = 0;
        virtual int32_t WriteByte(uint8_t byte) = 0;
        virtual int64_t Seek(int64_t offset, SeekOrigin origin) { return 0 };
    };

    class Stream : public ReadStream, public WriteStream
    {
    public:

        virtual ~Stream() = default;

        virtual void CopyToAsync(std::shared_ptr<Stream> destination, std::function<void(std::exception_ptr)> callback) NOEXCEPT = 0;
        virtual void CopyToAsync(std::shared_ptr<Stream> destination, uint32_t bufferSize, std::function<void(std::exception_ptr)> callback) NOEXCEPT = 0;

        virtual void CopyTo(std::shared_ptr<Stream> destination) = 0;
        virtual void CopyTo(std::shared_ptr<Stream> destination, uint32_t bufferSize) = 0;
    };
}
