#pragma once

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <boost/noncopyable.hpp>

#include "Utility.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Net {
        namespace Sockets {
            class Socket;
            class IPAddress;
            class IPEndPoint;
            class TcpClient;

            class LUPUS_API TcpListener : public boost::noncopyable
            {
            public:

                TcpListener(std::shared_ptr<IPEndPoint> localEP) throw(socket_error, null_pointer);
                TcpListener(std::shared_ptr<IPAddress> localaddr, uint16_t port) throw(socket_error, null_pointer);
                virtual ~TcpListener() = default;

                virtual bool IsActive() const throw(socket_error);
                virtual bool ExclusiveAddressUse() const throw(socket_error);
                virtual void ExclusiveAddressUse(bool) throw(socket_error);
                virtual std::shared_ptr<IPEndPoint> LocalEndPoint() const NOEXCEPT;
                virtual std::shared_ptr<Socket> Server() const NOEXCEPT;

                virtual void AcceptSocketAsync(std::function<void(std::exception_ptr, std::shared_ptr<Socket>)>) NOEXCEPT;
                virtual void AcceptTcpClientAsync(std::function<void(std::exception_ptr, std::shared_ptr<TcpClient>)>) NOEXCEPT;

                virtual std::shared_ptr<Socket> AcceptSocket() throw(socket_error);
                virtual std::shared_ptr<TcpClient> AcceptTcpClient() throw(socket_error);
                virtual void Start() throw(socket_error);
                virtual void Start(int backlog) throw(socket_error);
                virtual void Stop() throw(socket_error);

            private:

                std::shared_ptr<Socket> mServer = nullptr;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
