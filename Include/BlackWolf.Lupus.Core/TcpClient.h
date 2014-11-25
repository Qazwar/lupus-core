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
                TcpClient(Pointer<IPEndPoint> localEP) throw(SocketError, NullPointer);
                TcpClient(const String& hostname, U16 port) throw(SocketError, RuntimeError);
                virtual ~TcpClient() = default;

                virtual U32 Available() const throw(InvalidOperation);
                virtual Pointer<Socket> Client() const NOEXCEPT;
                virtual void Client(Pointer<Socket>) NOEXCEPT;
                virtual bool IsConnected() const NOEXCEPT;
                virtual bool ExclusiveAddressUse() const throw(SocketError);
                virtual void ExclusiveAddressUse(bool) throw(SocketError);
                virtual bool NoDelay() const throw(SocketError, InvalidOperation);
                virtual void NoDelay(bool) throw(SocketError, InvalidOperation);
                virtual int SendBuffer() const throw(SocketError, InvalidOperation);
                virtual void SendBuffer(int) throw(SocketError, InvalidOperation);
                virtual int ReceiveBuffer() const throw(SocketError, InvalidOperation);
                virtual void ReceiveBuffer(int) throw(SocketError, InvalidOperation);
                /*!
                 * Wert in Millisekunden.
                 */
                virtual int SendTimeout() const throw(InvalidOperation);
                /*!
                 * Wert in Millisekunden.
                 */
                virtual void SendTimeout(int) throw(SocketError, InvalidOperation);
                /*!
                 * Wert in Millisekunden.
                 */
                virtual int ReceiveTimeout() const throw(InvalidOperation);
                /*!
                 * Wert in Millisekunden.
                 */
                virtual void ReceiveTimeout(int) throw(SocketError, InvalidOperation);

                virtual Task<void> ConnectAsync(Pointer<IPEndPoint> remoteEndPoint) NOEXCEPT;
                virtual Task<void> ConnectAsync(Pointer<IPAddress> address, U16 port) NOEXCEPT;
                virtual Task<void> ConnectAsync(const Vector<Pointer<IPEndPoint>>& endPoints) NOEXCEPT;
                virtual Task<void> ConnectAsync(const String& host, U16 port) throw(InvalidArgument);

                virtual void Connect(Pointer<IPEndPoint> remoteEndPoint) throw(SocketError, InvalidOperation);
                virtual void Connect(Pointer<IPAddress> address, U16 port) throw(SocketError, InvalidOperation);
                virtual void Connect(const Vector<Pointer<IPEndPoint>>& endPoints) throw(InvalidOperation);
                virtual void Connect(const String& host, U16 port) throw(SocketError, InvalidArgument, InvalidOperation);
                virtual void Close() throw(SocketError, InvalidOperation);
                virtual Pointer<NetworkStream> GetStream() const throw(InvalidOperation);

            private:

                Pointer<Socket> mClient = nullptr;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
