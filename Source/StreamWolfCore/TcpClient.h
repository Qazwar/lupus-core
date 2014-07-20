#pragma once

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <boost/noncopyable.hpp>

#include "Utility.h"
#include "SocketEnum.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace StreamWolf {
    namespace Net {
        namespace Sockets {
            class Socket;
            class IPAddress;
            class IPEndPoint;
            class NetworkStream;

            class SWC_API TcpClient : public boost::noncopyable
            {
            public:

                TcpClient() = default;
                TcpClient(AddressFamily family) NOEXCEPT;
                TcpClient(std::shared_ptr<IPEndPoint> localEP) throw(socket_error, null_pointer);
                TcpClient(const std::string& hostname, uint16_t port) throw(socket_error, std::runtime_error);
                virtual ~TcpClient() = default;

                virtual uint32_t Available() const throw(null_pointer);
                virtual std::shared_ptr<Socket> Client() const NOEXCEPT;
                virtual void Client(std::shared_ptr<Socket>) throw(null_pointer);
                virtual bool IsConnected() const NOEXCEPT;
                virtual bool ExclusiveAddressUse() const throw(socket_error);
                virtual void ExclusiveAddressUse(bool) throw(socket_error);
                virtual bool NoDelay() const throw(socket_error, null_pointer);
                virtual void NoDelay(bool) throw(socket_error, null_pointer);
                virtual int32_t SendBuffer() const throw(socket_error, null_pointer);
                virtual void SendBuffer(int32_t) throw(socket_error, null_pointer);
                virtual int32_t ReceiveBuffer() const throw(socket_error, null_pointer);
                virtual void ReceiveBuffer(int32_t) throw(socket_error, null_pointer);
                virtual int32_t SendTimeout() const throw(null_pointer);
                virtual void SendTimeout(int32_t) throw(socket_error, null_pointer);
                virtual int32_t ReceiveTimeout() const throw(null_pointer);
                virtual void ReceiveTimeout(int32_t) throw(socket_error, null_pointer);

                virtual void ConnectAsync(std::shared_ptr<IPEndPoint> remoteEndPoint, std::function<void(std::exception_ptr, TcpClient*)>) NOEXCEPT;
                virtual void ConnectAsync(std::shared_ptr<IPAddress> address, uint16_t port, std::function<void(std::exception_ptr, TcpClient*)>) NOEXCEPT;
                virtual void ConnectAsync(const std::vector<std::shared_ptr<IPEndPoint>>& endPoints, std::function<void(std::exception_ptr, TcpClient*)>) NOEXCEPT;
                virtual void ConnectAsync(const std::string& host, uint16_t port, std::function<void(std::exception_ptr, TcpClient*)>) NOEXCEPT;

                virtual void Connect(std::shared_ptr<IPEndPoint> remoteEndPoint) throw(socket_error, null_pointer);
                virtual void Connect(std::shared_ptr<IPAddress> address, uint16_t port) throw(socket_error, null_pointer);
                virtual void Connect(const std::vector<std::shared_ptr<IPEndPoint>>& endPoints) throw(null_pointer);
                virtual void Connect(const std::string& host, uint16_t port) throw(socket_error, std::invalid_argument, null_pointer);
                virtual void Close() throw(socket_error, null_pointer);
                virtual std::shared_ptr<NetworkStream> GetStream() const throw(null_pointer);

            private:

                std::shared_ptr<Socket> mClient = nullptr;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
