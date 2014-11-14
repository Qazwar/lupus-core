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
            class TcpClient;

            class LUPUSCORE_API TcpListener : public NonCopyable
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

                virtual Task<std::shared_ptr<Socket>> AcceptSocketAsync() NOEXCEPT;
                virtual Task<std::shared_ptr<TcpClient>> AcceptTcpClientAsync() NOEXCEPT;

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
