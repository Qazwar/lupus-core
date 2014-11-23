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
#include "TcpListener.h"
#include "TcpClient.h"
#include "Socket.h"
#include "IPAddress.h"
#include "IPEndPoint.h"

#include <thread>



namespace Lupus {
    namespace Net {
        namespace Sockets {
            TcpListener::TcpListener(Pointer<IPEndPoint> localEP)
            {
                if (!localEP) {
                    throw NullPointer("localEP");
                }

                mServer = MakePointer<Socket>(localEP->Family(), SocketType::Stream, ProtocolType::TCP);
                mServer->Bind(localEP);
            }

            TcpListener::TcpListener(Pointer<IPAddress> localaddr, uint16_t port)
            {
                if (!localaddr) {
                    throw NullPointer("localaddr");
                }

                auto ep = MakePointer<IPEndPoint>(localaddr, port);
                mServer = MakePointer<Socket>(localaddr->Family(), SocketType::Stream, ProtocolType::TCP);
                mServer->Bind(ep);
            }

            bool TcpListener::IsActive() const
            {
                return mServer->IsListening();
            }

            bool TcpListener::ExclusiveAddressUse() const
            {
                int result, length = 4;

                if (getsockopt(mServer->Handle(), SOL_SOCKET, SO_REUSEADDR, (char*)&result, (int*)&length) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }

                return (result != 0);
            }

            void TcpListener::ExclusiveAddressUse(bool value)
            {
                int val = value ? 1 : 0;

                if (setsockopt(mServer->Handle(), SOL_SOCKET, SO_REUSEADDR, (char*)&val, 4) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }
            }

            Pointer<IPEndPoint> TcpListener::LocalEndPoint() const
            {
                return mServer->LocalEndPoint();
            }

            Pointer<Socket> TcpListener::Server() const
            {
                return mServer;
            }

            Task<Pointer<Socket>> TcpListener::AcceptSocketAsync()
            {
                return Task<Pointer<Socket>>([this]() {
                    return this->AcceptSocket();
                });
            }

            Task<Pointer<TcpClient>> TcpListener::AcceptTcpClientAsync()
            {
                return Task<Pointer<TcpClient>>([this]() {
                    return this->AcceptTcpClient();
                });
            }

            Pointer<Socket> TcpListener::AcceptSocket()
            {
                return mServer->Accept();
            }

            Pointer<TcpClient> TcpListener::AcceptTcpClient()
            {
                auto client = MakePointer<TcpClient>();
                client->Client(AcceptSocket());
                return client;
            }

            void TcpListener::Start()
            {
                mServer->Listen(10);
            }

            void TcpListener::Start(int backlog)
            {
                mServer->Listen(backlog);
            }

            void TcpListener::Stop()
            {
                mServer->Close();
            }
        }
    }
}
