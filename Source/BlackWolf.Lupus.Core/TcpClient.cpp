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
#include "TcpClient.h"
#include "Socket.h"
#include "IPEndPoint.h"
#include "IPAddress.h"
#include "NetworkStream.h"
#include "NetUtility.h"
#include "Integer.h"

#include <thread>



namespace Lupus {
    namespace Net {
        namespace Sockets {
            TcpClient::TcpClient(AddressFamily family)
            {
                mClient = MakePointer<Socket>(family, SocketType::Stream, ProtocolType::TCP);
            }

            TcpClient::TcpClient(Pointer<IPEndPoint> localEP)
            {
                if (!localEP) {
                    throw NullPointer("localEP");
                }

                mClient = MakePointer<Socket>(localEP->Family(), SocketType::Stream, ProtocolType::TCP);
                mClient->Connect(localEP);
            }

            TcpClient::TcpClient(const String& hostname, U16 port)
            {
                GetAddressInformation(hostname, Integer::ToString(port), AddressFamily::Unspecified, SocketType::Stream, ProtocolType::TCP);
                mClient = MakePointer<Socket>(AddressFamily::Unspecified, SocketType::Stream, ProtocolType::TCP);
                mClient->Connect(GetAddressInformation(hostname, Integer::ToString(port), AddressFamily::Unspecified, SocketType::Stream, ProtocolType::TCP));
            }

            U32 TcpClient::Available() const
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                return mClient->Available();
            }

            Pointer<Socket> TcpClient::Client() const
            {
                return mClient;
            }

            void TcpClient::Client(Pointer<Socket> client)
            {
                mClient = client;
            }

            bool TcpClient::IsConnected() const
            {
                if (mClient) {
                    return mClient->IsConnected();
                }

                return false;
            }

            bool TcpClient::ExclusiveAddressUse() const
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                int result, length = 4;

                if (getsockopt(mClient->Handle(), SOL_SOCKET, SO_REUSEADDR, (char*)&result, (int*)&length) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }

                return (result != 0);
            }

            void TcpClient::ExclusiveAddressUse(bool value)
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                int val = value ? 1 : 0;

                if (setsockopt(mClient->Handle(), SOL_SOCKET, SO_REUSEADDR, (char*)&val, 4) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }
            }

            bool TcpClient::NoDelay() const
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                return mClient->NoDelay();
            }

            void TcpClient::NoDelay(bool b)
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                mClient->NoDelay(b);
            }

            int TcpClient::SendBuffer() const
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                return mClient->SendBuffer();
            }

            void TcpClient::SendBuffer(int i)
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                mClient->SendBuffer(i);
            }

            int TcpClient::ReceiveBuffer() const
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                return mClient->ReceiveBuffer();
            }

            void TcpClient::ReceiveBuffer(int i)
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                mClient->ReceiveBuffer(i);
            }

            int TcpClient::SendTimeout() const
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                return mClient->SendTimeout();
            }

            void TcpClient::SendTimeout(int i)
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                mClient->SendTimeout(i);
            }

            int TcpClient::ReceiveTimeout() const
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                return mClient->ReceiveTimeout();
            }

            void TcpClient::ReceiveTimeout(int i)
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                mClient->ReceiveTimeout(i);
            }

            Task<void> TcpClient::ConnectAsync(Pointer<IPEndPoint> remoteEndPoint)
            {
                return Task<void>([this, remoteEndPoint]() {
                    this->Connect(remoteEndPoint);
                });
            }

            Task<void> TcpClient::ConnectAsync(Pointer<IPAddress> address, U16 port)
            {
                return Task<void>([this, address, port]() {
                    this->Connect(address, port);
                });
            }

            Task<void> TcpClient::ConnectAsync(const Vector<Pointer<IPEndPoint>>& endPoints)
            {
                return Task<void>([this, &endPoints]() {
                    this->Connect(endPoints);
                });
            }

            Task<void> TcpClient::ConnectAsync(const String& host, U16 port)
            {
                return Task<void>([this, &host, port]() {
                    this->Connect(host, port);
                });
            }

            void TcpClient::Connect(Pointer<IPEndPoint> remoteEndPoint)
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                mClient->Connect(remoteEndPoint);
            }

            void TcpClient::Connect(Pointer<IPAddress> address, U16 port)
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                mClient->Connect(address, port);
            }

            void TcpClient::Connect(const Vector<Pointer<IPEndPoint>>& endPoints)
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                mClient->Connect(endPoints);
            }

            void TcpClient::Connect(const String& host, U16 port)
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                mClient->Connect(host, port);
            }

            void TcpClient::Close()
            {
                if (!mClient) {
                    throw InvalidOperation("TcpClient is in an invalid state");
                }

                mClient->Close();
            }

            Pointer<NetworkStream> TcpClient::GetStream() const
            {
                return MakePointer<NetworkStream>(mClient);
            }
        }
    }
}
