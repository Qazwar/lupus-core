#pragma once

#include "Stream.h"

namespace StreamWolf {
    class SWC_API MemoryStream : public Stream
    {
    public:

        MemoryStream() = default;
        MemoryStream(const std::vector<uint8_t>&);
        MemoryStream(uint32_t size);
        MemoryStream(const std::vector<uint8_t>&, bool writable);
        MemoryStream(const std::vector<uint8_t>&, uint32_t offset, uint32_t size);
        MemoryStream(const std::vector<uint8_t>&, uint32_t offset, uint32_t size, bool writable);
        MemoryStream(const std::vector<uint8_t>&, uint32_t offset, uint32_t size, bool writable, bool visible);
        virtual ~MemoryStream() = default;

        virtual void Close() override;
        virtual int64_t Length() const override;
        virtual void Length(int64_t) throw(std::out_of_range) override;
        virtual int64_t Position() const override;
        virtual void Position(int64_t) throw(std::out_of_range) override;
        virtual int32_t Read(std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size) throw(std::out_of_range) override;
        virtual int32_t ReadByte() override;
        virtual int32_t Write(const std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size) throw(not_supported, std::out_of_range) override;
        virtual void WriteByte(uint8_t byte) throw(not_supported) override;
        virtual int64_t Seek(int64_t offset, SeekOrigin origin) override;

        virtual uint32_t Capacity() const;
        virtual void Capacity(uint32_t);
        virtual const std::vector<uint8_t>& GetBuffer() const throw(not_supported);

        virtual uint8_t& operator[](uint32_t);
        virtual const uint8_t& operator[](uint32_t) const;

    private:

        bool mWritable = true;
        bool mVisible = true;
        std::vector<uint8_t> mBuffer;
        std::vector<uint8_t>::iterator mIterator;
    };
}
