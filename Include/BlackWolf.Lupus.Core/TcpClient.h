/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Lupus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lupus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lupus. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <boost/noncopyable.hpp>

#include "String.h"
#include "SocketEnum.h"
#include "Task.h"

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
            class NetworkStream;

            class LUPUSCORE_API TcpClient : public boost::noncopyable
            {
            public:

                TcpClient() = default;
                TcpClient(AddressFamily family) NOEXCEPT;
                TcpClient(std::shared_ptr<IPEndPoint> localEP) throw(socket_error, null_pointer);
                TcpClient(const String& hostname, uint16_t port) throw(socket_error, std::runtime_error);
                virtual ~TcpClient() = default;

                virtual size_t Available() const throw(invalid_operation);
                virtual std::shared_ptr<Socket> Client() const NOEXCEPT;
                virtual void Client(std::shared_ptr<Socket>) NOEXCEPT;
                virtual bool IsConnected() const NOEXCEPT;
                virtual bool ExclusiveAddressUse() const throw(socket_error);
                virtual void ExclusiveAddressUse(bool) throw(socket_error);
                virtual bool NoDelay() const throw(socket_error, invalid_operation);
                virtual void NoDelay(bool) throw(socket_error, invalid_operation);
                virtual int SendBuffer() const throw(socket_error, invalid_operation);
                virtual void SendBuffer(int) throw(socket_error, invalid_operation);
                virtual int ReceiveBuffer() const throw(socket_error, invalid_operation);
                virtual void ReceiveBuffer(int) throw(socket_error, invalid_operation);
                /*!
                 * Wert in Millisekunden.
                 */
                virtual int SendTimeout() const throw(invalid_operation);
                /*!
                 * Wert in Millisekunden.
                 */
                virtual void SendTimeout(int) throw(socket_error, invalid_operation);
                /*!
                 * Wert in Millisekunden.
                 */
                virtual int ReceiveTimeout() const throw(invalid_operation);
                /*!
                 * Wert in Millisekunden.
                 */
                virtual void ReceiveTimeout(int) throw(socket_error, invalid_operation);

                virtual Task<void> ConnectAsync(std::shared_ptr<IPEndPoint> remoteEndPoint) NOEXCEPT;
                virtual Task<void> ConnectAsync(std::shared_ptr<IPAddress> address, uint16_t port) NOEXCEPT;
                virtual Task<void> ConnectAsync(const std::vector<std::shared_ptr<IPEndPoint>>& endPoints) NOEXCEPT;
                virtual Task<void> ConnectAsync(const String& host, uint16_t port) throw(std::invalid_argument);

                virtual void Connect(std::shared_ptr<IPEndPoint> remoteEndPoint) throw(socket_error, invalid_operation);
                virtual void Connect(std::shared_ptr<IPAddress> address, uint16_t port) throw(socket_error, invalid_operation);
                virtual void Connect(const std::vector<std::shared_ptr<IPEndPoint>>& endPoints) throw(invalid_operation);
                virtual void Connect(const String& host, uint16_t port) throw(socket_error, std::invalid_argument, invalid_operation);
                virtual void Close() throw(socket_error, invalid_operation);
                virtual std::shared_ptr<NetworkStream> GetStream() const throw(invalid_operation);

            private:

                std::shared_ptr<Socket> mClient = nullptr;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
