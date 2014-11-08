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
#include "TcpListener.h"
#include "TcpClient.h"
#include "Socket.h"
#include "IPAddress.h"
#include "IPEndPoint.h"

#include <thread>

using namespace std;

namespace Lupus {
    namespace Net {
        namespace Sockets {
            TcpListener::TcpListener(shared_ptr<IPEndPoint> localEP)
            {
                if (!localEP) {
                    throw null_pointer();
                }

                mServer = make_shared<Socket>(localEP->Family(), SocketType::Stream, ProtocolType::TCP);
                mServer->Bind(localEP);
            }

            TcpListener::TcpListener(shared_ptr<IPAddress> localaddr, uint16_t port)
            {
                if (!localaddr) {
                    throw null_pointer();
                }

                auto ep = make_shared<IPEndPoint>(localaddr, port);
                mServer = make_shared<Socket>(localaddr->Family(), SocketType::Stream, ProtocolType::TCP);
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
                    throw socket_error(GetLastSocketErrorString());
                }

                return (result != 0);
            }

            void TcpListener::ExclusiveAddressUse(bool value)
            {
                int val = value ? 1 : 0;

                if (setsockopt(mServer->Handle(), SOL_SOCKET, SO_REUSEADDR, (char*)&val, 4) != 0) {
                    throw socket_error(GetLastSocketErrorString());
                }
            }

            shared_ptr<IPEndPoint> TcpListener::LocalEndPoint() const
            {
                return mServer->LocalEndPoint();
            }

            shared_ptr<Socket> TcpListener::Server() const
            {
                return mServer;
            }

            Task<shared_ptr<Socket>> TcpListener::AcceptSocketAsync()
            {
                return Task<shared_ptr<Socket>>([this]() {
                    return this->AcceptSocket();
                });
            }

            Task<shared_ptr<TcpClient>> TcpListener::AcceptTcpClientAsync()
            {
                return Task<shared_ptr<TcpClient>>([this]() {
                    return this->AcceptTcpClient();
                });
            }

            shared_ptr<Socket> TcpListener::AcceptSocket()
            {
                return mServer->Accept();
            }

            shared_ptr<TcpClient> TcpListener::AcceptTcpClient()
            {
                auto client = make_shared<TcpClient>();
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
