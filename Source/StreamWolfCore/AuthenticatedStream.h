#pragma once

#include "Stream.h"

namespace StreamWolf {
    namespace Net {
        namespace Security {
            class AuthenticatedSteram : public ReadStream, public WriteStream
            {
            public:

                virtual ~AuthenticatedSteram() = default;

                virtual void ReadAsync(std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size, std::function<void(std::exception_ptr, int32_t)> callback) NOEXCEPT override;
                virtual void WriteAsync(const std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size, std::function<void(std::exception_ptr, int32_t)> callback) NOEXCEPT override;

                virtual void Close() override;
                virtual int64_t Length() const override;
                virtual int32_t Read(std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size) override;
                virtual int32_t ReadByte() override;
                virtual int32_t Write(const std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size) override;
                virtual int32_t WriteByte(uint8_t byte) override;

            protected:

                AuthenticatedSteram(std::shared_ptr<Stream> innerStream, bool leaveInnerStreamOpen);
            };
        }
    }
}
