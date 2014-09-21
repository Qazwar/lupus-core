#pragma once

#include "String.h"
#include "Stream.h"

namespace Lupus {
    namespace IO {
        class LUPUS_API StringStream : public Stream
        {
        public:

            StringStream(String str);
            virtual ~StringStream() = default;

            virtual bool CanRead() const override;
            virtual bool CanWrite() const override;
            virtual bool CanSeek() const override;

            virtual void Close() throw(not_supported) override;
            virtual int64_t Length() const NOEXCEPT override;
            virtual void Length(int64_t) NOEXCEPT override;
            virtual int64_t Position() const NOEXCEPT override;
            virtual void Position(int64_t) NOEXCEPT override;
            virtual int Read(std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::out_of_range) override;
            virtual int ReadByte() NOEXCEPT override;
            virtual int Write(const std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::out_of_range) override;
            virtual void WriteByte(uint8_t byte) NOEXCEPT override;
            virtual int64_t Seek(int64_t offset, SeekOrigin origin) NOEXCEPT override;

        private:

            StringStream() = delete;
            StringStream(const StringStream&) = delete;
            StringStream(StringStream&&) = delete;

            String mString;
            String::iterator mPosition = 0;
        };
    }
}
