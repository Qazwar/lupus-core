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
                UdpClient(U16 port); // Bind
                UdpClient(Pointer<IPEndPoint> ep) throw(NullPointer); // Bind
                UdpClient(U16 port, AddressFamily); // Bind
                UdpClient(const String& hostname, U16 port); // Connect
                virtual ~UdpClient() = default;

                virtual U32 Available() const throw(InvalidOperation);
                virtual Pointer<Socket> Client() const NOEXCEPT;
                virtual void Client(Pointer<Socket>) NOEXCEPT;
                virtual bool ExclusiveAddressUse() const throw(SocketError);
                virtual void ExclusiveAddressUse(bool) throw(SocketError);

                virtual Task<Vector<U8>> ReceiveAsync(Pointer<IPEndPoint>&) NOEXCEPT;
                virtual Task<int> SendAsync(const Vector<U8>&, U32) NOEXCEPT;
                virtual Task<int> SendAsync(const Vector<U8>&, U32, Pointer<IPEndPoint>) NOEXCEPT;
                virtual Task<int> SendAsync(const Vector<U8>&, U32, const String&, U16) NOEXCEPT;

                virtual void Connect(Pointer<IPEndPoint> remoteEndPoint) throw(SocketError, InvalidOperation);
                virtual void Connect(Pointer<IPAddress> address, U16 port) throw(SocketError, InvalidOperation);
                virtual void Connect(const String& host, U16 port) throw(SocketError, InvalidArgument, InvalidOperation);
                virtual void Close() throw(SocketError, InvalidOperation);
                virtual Vector<U8> Receive(Pointer<IPEndPoint>&) throw(SocketError);
                virtual int Send(const Vector<U8>&, U32) throw(SocketError);
                virtual int Send(const Vector<U8>&, U32, Pointer<IPEndPoint>);
                virtual int Send(const Vector<U8>&, U32, const String&, U16) throw(InvalidArgument);

            private:

                Pointer<Socket> mClient = nullptr;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
