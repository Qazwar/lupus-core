/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once

#include <tuple>
#include <vector>
#include <memory>
#include <functional>
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

            class LUPUSCORE_API UdpClient : public NonCopyable
            {
            public:

                UdpClient() = default;
                UdpClient(AddressFamily); // Socket
                UdpClient(uint16_t port); // Bind
                UdpClient(std::shared_ptr<IPEndPoint> ep) throw(null_pointer); // Bind
                UdpClient(uint16_t port, AddressFamily); // Bind
                UdpClient(const String& hostname, uint16_t port); // Connect
                virtual ~UdpClient() = default;

                virtual size_t Available() const throw(invalid_operation);
                virtual std::shared_ptr<Socket> Client() const NOEXCEPT;
                virtual void Client(std::shared_ptr<Socket>) NOEXCEPT;
                virtual bool ExclusiveAddressUse() const throw(socket_error);
                virtual void ExclusiveAddressUse(bool) throw(socket_error);

                virtual Task<std::vector<uint8_t>> ReceiveAsync(std::shared_ptr<IPEndPoint>&) NOEXCEPT;
                virtual Task<int> SendAsync(const std::vector<uint8_t>&, size_t) NOEXCEPT;
                virtual Task<int> SendAsync(const std::vector<uint8_t>&, size_t, std::shared_ptr<IPEndPoint>) NOEXCEPT;
                virtual Task<int> SendAsync(const std::vector<uint8_t>&, size_t, const String&, uint16_t) NOEXCEPT;

                virtual void Connect(std::shared_ptr<IPEndPoint> remoteEndPoint) throw(socket_error, invalid_operation);
                virtual void Connect(std::shared_ptr<IPAddress> address, uint16_t port) throw(socket_error, invalid_operation);
                virtual void Connect(const String& host, uint16_t port) throw(socket_error, std::invalid_argument, invalid_operation);
                virtual void Close() throw(socket_error, invalid_operation);
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
