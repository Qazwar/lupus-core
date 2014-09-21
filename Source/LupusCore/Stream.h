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

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

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

        virtual Task<void> CopyToAsync(std::shared_ptr<Stream> destination) NOEXCEPT;
        virtual Task<void> FlushAsync() NOEXCEPT;
        virtual Task<int> ReadAsync(std::vector<uint8_t>& buffer, size_t offset, size_t size) NOEXCEPT;
        virtual Task<int> WriteAsync(const std::vector<uint8_t>& buffer, size_t offset, size_t size) NOEXCEPT;

        virtual bool CanRead() const = 0;
        virtual bool CanWrite() const = 0;
        virtual bool CanSeek() const = 0;

        virtual void Close() = 0;
        virtual void CopyTo(std::shared_ptr<Stream> destination) throw(null_pointer, not_supported);
        virtual void Flush() throw(not_supported);
        virtual int64_t Length() const = 0;
        virtual void Length(int64_t) throw(not_supported);
        virtual int64_t Position() const = 0;
        virtual void Position(int64_t) throw(not_supported);
        virtual int Read(std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::out_of_range) = 0;
        virtual int ReadByte() = 0;
        virtual int Write(const std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::out_of_range) = 0;
        virtual void WriteByte(uint8_t byte) = 0;
        virtual int64_t Seek(int64_t offset, SeekOrigin origin) throw(not_supported);
    };

    //! Readonly adapter
    class LUPUS_API InputStream : public Stream
    {
    public:

        InputStream() = delete;
        InputStream(std::shared_ptr<Stream> innerStream) throw(std::invalid_argument);
        virtual ~InputStream() = default;

        virtual bool CanRead() const NOEXCEPT override;
        virtual bool CanWrite() const NOEXCEPT override;
        virtual bool CanSeek() const NOEXCEPT override;

        virtual void Close() override;
        virtual void CopyTo(std::shared_ptr<Stream> destination) throw(null_pointer, not_supported) override;
        virtual void Flush() override;
        virtual int64_t Length() const override;
        virtual void Length(int64_t) throw(not_supported) override;
        virtual int64_t Position() const override;
        virtual void Position(int64_t) throw(not_supported) override;
        virtual int Read(std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::out_of_range) override;
        virtual int ReadByte() override;
        virtual int Write(const std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(not_supported) override;
        virtual void WriteByte(uint8_t byte) throw(not_supported) override;
        virtual int64_t Seek(int64_t offset, SeekOrigin origin) override;

    private:

        std::shared_ptr<Stream> mInnerStream;
    };

    // Writeonly adapter
    class LUPUS_API OutputStream : public Stream
    {
    public:

        OutputStream() = delete;
        OutputStream(std::shared_ptr<Stream> innerStream) throw(std::invalid_argument);
        virtual ~OutputStream() = default;

        virtual bool CanRead() const NOEXCEPT override;
        virtual bool CanWrite() const NOEXCEPT override;
        virtual bool CanSeek() const NOEXCEPT override;

        virtual void Close() override;
        virtual void CopyTo(std::shared_ptr<Stream> destination) throw(null_pointer, not_supported) override;
        virtual void Flush() override;
        virtual int64_t Length() const override;
        virtual void Length(int64_t) throw(not_supported) override;
        virtual int64_t Position() const override;
        virtual void Position(int64_t) throw(not_supported) override;
        virtual int Read(std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::out_of_range) override;
        virtual int ReadByte() override;
        virtual int Write(const std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(not_supported) override;
        virtual void WriteByte(uint8_t byte) throw(not_supported) override;
        virtual int64_t Seek(int64_t offset, SeekOrigin origin) override;

    private:

        std::shared_ptr<Stream> mInnerStream;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
