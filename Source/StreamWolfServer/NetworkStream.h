#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include <exception>
#include <functional>
#include <boost/noncopyable.hpp>

#include "Utility.h"

namespace StreamWolf {
    namespace Net {
        namespace Sockets {
            class Socket;

            class NetworkStream : public boost::noncopyable
            {
            public:

                NetworkStream(std::shared_ptr<Socket> socket) throw(null_pointer);
                virtual ~NetworkStream() = default;

                virtual uint32_t DataAvailable() const throw(socket_error);
                virtual std::shared_ptr<Socket> Socket() const;

                virtual void ReadAsync(std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size, std::function<void(std::exception_ptr, int32_t)> callback) NOEXCEPT;
                virtual void WriteAsync(const std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size, std::function<void(std::exception_ptr, int32_t)> callback) NOEXCEPT;
                
                virtual void Close() throw(socket_error);
                virtual void Close(uint32_t timeout) throw(socket_error);
                virtual int32_t Read(std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size) throw(socket_error);
                virtual int32_t ReadByte() throw(socket_error);
                virtual int32_t Write(const std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size) throw(socket_error);
                virtual int32_t WriteByte(uint8_t byte) throw(socket_error);

            private:

                std::shared_ptr<Sockets::Socket> mSocket;
            };
        }
    }
}
