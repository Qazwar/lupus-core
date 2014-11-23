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
                UdpClient(Pointer<IPEndPoint> ep) throw(NullPointer); // Bind
                UdpClient(uint16_t port, AddressFamily); // Bind
                UdpClient(const String& hostname, uint16_t port); // Connect
                virtual ~UdpClient() = default;

                virtual size_t Available() const throw(InvalidOperation);
                virtual Pointer<Socket> Client() const NOEXCEPT;
                virtual void Client(Pointer<Socket>) NOEXCEPT;
                virtual bool ExclusiveAddressUse() const throw(SocketError);
                virtual void ExclusiveAddressUse(bool) throw(SocketError);

                virtual Task<Vector<uint8_t>> ReceiveAsync(Pointer<IPEndPoint>&) NOEXCEPT;
                virtual Task<int> SendAsync(const Vector<uint8_t>&, size_t) NOEXCEPT;
                virtual Task<int> SendAsync(const Vector<uint8_t>&, size_t, Pointer<IPEndPoint>) NOEXCEPT;
                virtual Task<int> SendAsync(const Vector<uint8_t>&, size_t, const String&, uint16_t) NOEXCEPT;

                virtual void Connect(Pointer<IPEndPoint> remoteEndPoint) throw(SocketError, InvalidOperation);
                virtual void Connect(Pointer<IPAddress> address, uint16_t port) throw(SocketError, InvalidOperation);
                virtual void Connect(const String& host, uint16_t port) throw(SocketError, InvalidArgument, InvalidOperation);
                virtual void Close() throw(SocketError, InvalidOperation);
                virtual Vector<uint8_t> Receive(Pointer<IPEndPoint>&) throw(SocketError);
                virtual int Send(const Vector<uint8_t>&, size_t) throw(SocketError);
                virtual int Send(const Vector<uint8_t>&, size_t, Pointer<IPEndPoint>);
                virtual int Send(const Vector<uint8_t>&, size_t, const String&, uint16_t) throw(InvalidArgument);

            private:

                Pointer<Socket> mClient = nullptr;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
