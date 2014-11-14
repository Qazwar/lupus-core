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

#include <vector>
#include <memory>
#include <functional>

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

            class LUPUSCORE_API TcpClient : public NonCopyable
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
