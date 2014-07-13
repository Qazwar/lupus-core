#pragma once

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <boost/noncopyable.hpp>

#include "SocketEnum.h"

namespace StreamWolf {
    namespace Net {
        namespace Sockets {
            class Socket;
            class IPAddress;
            class IPEndPoint;

            class UdpClient : public boost::noncopyable
            {
            public:

                UdpClient() = default;
                UdpClient(AddressFamily);
                UdpClient(uint16_t port);
                UdpClient(std::shared_ptr<IPEndPoint>);
                UdpClient(uint16_t port, AddressFamily);
                UdpClient(const std::string& hostname, uint16_t port);
                virtual ~UdpClient() = default;

                virtual uint32_t Available() const throw(null_pointer);
                virtual std::shared_ptr<Socket> Client() const NOEXCEPT;
                virtual void Client(std::shared_ptr<Socket>) throw(null_pointer);
                virtual bool ExclusiveAddressUse() const throw(socket_error);
                virtual void ExclusiveAddressUse(bool) throw(socket_error);

                virtual void ReceiveAsync(std::function<void(std::exception_ptr, std::shared_ptr<IPEndPoint>, const std::vector<uint8_t>&)>);
                virtual void SendAsync(const std::vector<uint8_t>&, uint32_t, std::function<void(std::exception_ptr, int32_t)>);
                virtual void SendAsync(const std::vector<uint8_t>&, uint32_t, std::shared_ptr<IPEndPoint>, std::function<void(std::exception_ptr, int32_t)>);
                virtual void SendAsync(const std::vector<uint8_t>&, uint32_t, const std::string&, uint16_t, std::function<void(std::exception_ptr, int32_t)>);

                virtual void Connect(std::shared_ptr<IPEndPoint> remoteEndPoint) throw(socket_error, null_pointer);
                virtual void Connect(std::shared_ptr<IPAddress> address, uint16_t port) throw(socket_error, null_pointer);
                virtual void Connect(const std::string& host, uint16_t port) throw(socket_error, std::invalid_argument, null_pointer);
                virtual void Close() throw(socket_error, null_pointer);
                virtual std::vector<uint8_t> Receive(std::shared_ptr<IPEndPoint>&) throw(socket_error);
                virtual int32_t Send(const std::vector<uint8_t>&, uint32_t) throw(socket_error);
                virtual int32_t Send(const std::vector<uint8_t>&, uint32_t, std::shared_ptr<IPEndPoint>);
                virtual int32_t Send(const std::vector<uint8_t>&, uint32_t, const std::string&, uint16_t) throw(std::invalid_argument);

            private:

                std::shared_ptr<Socket> mClient = nullptr;
            };
        }
    }
}
