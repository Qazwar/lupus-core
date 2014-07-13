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
        namespace Socket {
            class Socket;

            class NetworkStream : public boost::noncopyable
            {
            public:

                NetworkStream(std::shared_ptr<Socket> socket) throw(null_pointer);
                virtual ~NetworkStream() = default;

                uint32_t DataAvailable() const throw(socket_error);
                std::shared_ptr<Socket> Handle() const;

                void ReadAsync(std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size, std::function<void(std::exception_ptr, const std::vector<uint8_t>&, int32_t)> callback) NOEXCEPT;
                void WriteAsync(const std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size, std::function<void(std::exception_ptr, const std::vector<uint8_t>&, int32_t)> callback) NOEXCEPT;
                
                void Close() throw(socket_error);
                void Close(uint32_t) throw(socket_error);
                int32_t Read(std::vector<uint8_t>&, uint32_t, uint32_t) throw(socket_error);
                int32_t ReadByte() throw(socket_error);
                int32_t Write(const std::vector<uint8_t>&, uint32_t, uint32_t) throw(socket_error);
                int32_t WriteByte(uint8_t) throw(socket_error);

            private:

                std::shared_ptr<Socket> mHandle;
            };
        }
    }
}
