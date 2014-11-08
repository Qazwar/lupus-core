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

#include <tuple>
#include <vector>
#include <memory>
#include <functional>
#include <boost/noncopyable.hpp>

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

            class LUPUSCORE_API UdpClient : public boost::noncopyable
            {
            public:

                UdpClient() = default;
                UdpClient(AddressFamily); // Socket
                UdpClient(uint16_t port); // Bind
                UdpClient(std::shared_ptr<IPEndPoint>); // Bind
                UdpClient(uint16_t port, AddressFamily); // Bind
                UdpClient(const String& hostname, uint16_t port); // Connect
                virtual ~UdpClient() = default;

                virtual size_t Available() const throw(null_pointer);
                virtual std::shared_ptr<Socket> Client() const NOEXCEPT;
                virtual void Client(std::shared_ptr<Socket>) throw(null_pointer);
                virtual bool ExclusiveAddressUse() const throw(socket_error);
                virtual void ExclusiveAddressUse(bool) throw(socket_error);

                virtual Task<std::vector<uint8_t>> ReceiveAsync(std::shared_ptr<IPEndPoint>&) NOEXCEPT;
                virtual Task<int> SendAsync(const std::vector<uint8_t>&, size_t) NOEXCEPT;
                virtual Task<int> SendAsync(const std::vector<uint8_t>&, size_t, std::shared_ptr<IPEndPoint>) NOEXCEPT;
                virtual Task<int> SendAsync(const std::vector<uint8_t>&, size_t, const String&, uint16_t) NOEXCEPT;

                virtual void Connect(std::shared_ptr<IPEndPoint> remoteEndPoint) throw(socket_error, null_pointer);
                virtual void Connect(std::shared_ptr<IPAddress> address, uint16_t port) throw(socket_error, null_pointer);
                virtual void Connect(const String& host, uint16_t port) throw(socket_error, std::invalid_argument, null_pointer);
                virtual void Close() throw(socket_error, null_pointer);
                virtual std::vector<uint8_t> Receive(std::shared_ptr<IPEndPoint>&) throw(socket_error);
                virtual int Send(const std::vector<uint8_t>&, size_t) throw(socket_error);
                virtual int Send(const std::vector<uint8_t>&, size_t, std::shared_ptr<IPEndPoint>);
                virtual int Send(const std::vector<uint8_t>&, size_t, const String&, uint16_t) throw(std::invalid_argument);

            private:

                std::shared_ptr<Socket> mClient = nullptr;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
