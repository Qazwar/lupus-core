#pragma once

#include "Stream.h"

namespace StreamWolf {
    namespace Net {
        namespace Sockets {
            class Socket;

            class NetworkStream : public ReadStream, public WriteStream
            {
            public:

                NetworkStream(std::shared_ptr<Socket> socket) throw(null_pointer);
                virtual ~NetworkStream() = default;

                virtual uint32_t DataAvailable() const throw(socket_error);
                virtual std::shared_ptr<Socket> Socket() const NOEXCEPT;

                virtual void ReadAsync(std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size, std::function<void(std::exception_ptr, int32_t)> callback) NOEXCEPT override;
                virtual void WriteAsync(const std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size, std::function<void(std::exception_ptr, int32_t)> callback) NOEXCEPT override;
                
                virtual void Close() throw(socket_error) override;
                virtual void Close(uint32_t timeout) throw(socket_error);
                virtual int64_t Length() const throw(socket_error) override;
                virtual int32_t Read(std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size) throw(socket_error) override;
                virtual int32_t ReadByte() throw(socket_error) override;
                virtual int32_t Write(const std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size) throw(socket_error) override;
                virtual int32_t WriteByte(uint8_t byte) throw(socket_error) override;

            private:

                std::shared_ptr<Sockets::Socket> mSocket;
            };
        }
    }
}
