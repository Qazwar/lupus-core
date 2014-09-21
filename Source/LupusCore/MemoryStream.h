#pragma once

#include "Stream.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    class LUPUS_API MemoryStream : public Stream
    {
    public:

        MemoryStream() = default;
        MemoryStream(const std::vector<uint8_t>&) NOEXCEPT;
        MemoryStream(size_t size) NOEXCEPT;
        MemoryStream(const std::vector<uint8_t>&, bool writable) NOEXCEPT;
        MemoryStream(const std::vector<uint8_t>&, size_t offset, size_t size) throw(std::out_of_range);
        MemoryStream(const std::vector<uint8_t>&, size_t offset, size_t size, bool writable) throw(std::out_of_range);
        MemoryStream(const std::vector<uint8_t>&, size_t offset, size_t size, bool writable, bool visible) throw(std::out_of_range);
        virtual ~MemoryStream() = default;

        virtual bool CanRead() const NOEXCEPT override;
        virtual bool CanWrite() const NOEXCEPT override;
        virtual bool CanSeek() const NOEXCEPT override;

        virtual void Close() NOEXCEPT override;
        virtual int64_t Length() const NOEXCEPT override;
        virtual void Length(int64_t) NOEXCEPT override;
        virtual int64_t Position() const NOEXCEPT override;
        virtual void Position(int64_t) NOEXCEPT override;
        virtual int Read(std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::out_of_range) override;
        virtual int ReadByte() NOEXCEPT override;
        virtual int Write(const std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(not_supported, std::out_of_range) override;
        virtual void WriteByte(uint8_t byte) throw(not_supported) override;
        virtual int64_t Seek(int64_t offset, SeekOrigin origin) NOEXCEPT override;

        virtual size_t Capacity() const;
        virtual void Capacity(size_t);
        virtual const std::vector<uint8_t>& GetBuffer() const throw(unauthorized_access);

        virtual uint8_t& operator[](size_t);
        virtual const uint8_t& operator[](size_t) const;

    private:

        bool mWritable = true;
        bool mVisible = true;
        std::vector<uint8_t> mBuffer;
        std::vector<uint8_t>::iterator mIterator;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
