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
#include "UdpClient.h"
#include "Socket.h"
#include "IPAddress.h"
#include "IPEndPoint.h"
#include "Integer.h"
#include "NetUtility.h"

#include <thread>

using namespace std;

namespace Lupus {
    namespace Net {
        namespace Sockets {
            UdpClient::UdpClient(AddressFamily family)
            {
                mClient = make_shared<Socket>(family, SocketType::Datagram, ProtocolType::UDP);
            }

            UdpClient::UdpClient(uint16_t port)
            {
                mClient = make_shared<Socket>(AddressFamily::Unspecified, SocketType::Datagram, ProtocolType::UDP);
                mClient->Bind(make_shared<IPEndPoint>(IPAddress::Loopback(), port));
            }

            UdpClient::UdpClient(shared_ptr<IPEndPoint> ep)
            {
                mClient = make_shared<Socket>(AddressFamily::Unspecified, SocketType::Datagram, ProtocolType::UDP);
                mClient->Bind(ep);
            }

            UdpClient::UdpClient(uint16_t port, AddressFamily family)
            {
                mClient = make_shared<Socket>(family, SocketType::Datagram, ProtocolType::UDP);
                mClient->Bind(make_shared<IPEndPoint>(IPAddress::Loopback(), port));
            }

            UdpClient::UdpClient(const String& hostname, uint16_t port)
            {
                mClient = make_shared<Socket>(AddressFamily::Unspecified, SocketType::Datagram, ProtocolType::UDP);
                mClient->Connect(GetAddressInformation(hostname, Integer::ToString(port), AddressFamily::Unspecified, SocketType::Datagram, ProtocolType::UDP));
            }

            size_t UdpClient::Available() const
            {
                if (!mClient) {
                    throw null_pointer("UdpClient is in an invalid state");
                }

                return mClient->Available();
            }

            shared_ptr<Socket> UdpClient::Client() const
            {
                return mClient;
            }

            void UdpClient::Client(shared_ptr<Socket> client)
            {
                if (!client) {
                    throw null_pointer("client");
                }

                mClient = client;
            }

            bool UdpClient::ExclusiveAddressUse() const
            {
                if (!mClient) {
                    throw null_pointer("UdpClient is in an invalid state");
                }

                int result, length = 4;

                if (getsockopt(mClient->Handle(), SOL_SOCKET, SO_REUSEADDR, (char*)&result, (int*)&length) != 0) {
                    throw socket_error(GetLastSocketErrorString());
                }

                return (result != 0);
            }

            void UdpClient::ExclusiveAddressUse(bool value)
            {
                if (!mClient) {
                    throw null_pointer("UdpClient is in an invalid state");
                }

                int val = value ? 1 : 0;

                if (setsockopt(mClient->Handle(), SOL_SOCKET, SO_REUSEADDR, (char*)&val, 4) != 0) {
                    throw socket_error(GetLastSocketErrorString());
                }
            }

            Task<std::vector<uint8_t>> UdpClient::ReceiveAsync(shared_ptr<IPEndPoint>& ep)
            {
                return Task<vector<uint8_t>>([this, &ep]() {
                    return this->Receive(ep);
                });
            }

            Task<int> UdpClient::SendAsync(const vector<uint8_t>& buffer, size_t size)
            {
                return Task<int>([this, &buffer, size]() {
                    return this->Send(buffer, size);
                });
            }

            Task<int> UdpClient::SendAsync(const vector<uint8_t>& buffer, size_t size, shared_ptr<IPEndPoint> ep)
            {
                return Task<int>([this, &buffer, size, ep]() {
                    return this->Send(buffer, size, ep);
                });
            }

            Task<int> UdpClient::SendAsync(const vector<uint8_t>& buffer, size_t size, const String& hostname, uint16_t port)
            {
                return Task<int>([this, &buffer, size, &hostname, port]() {
                    return this->Send(buffer, size, hostname, port);
                });
            }

            void UdpClient::Connect(shared_ptr<IPEndPoint> remoteEndPoint)
            {
                if (!mClient) {
                    throw null_pointer("UdpClient is in an invalid state");
                }

                mClient->Connect(remoteEndPoint);
            }

            void UdpClient::Connect(shared_ptr<IPAddress> address, uint16_t port)
            {
                if (!mClient) {
                    throw null_pointer("UdpClient is in an invalid state");
                }

                mClient->Connect(address, port);
            }

            void UdpClient::Connect(const String& host, uint16_t port)
            {
                if (!mClient) {
                    throw null_pointer("UdpClient is in an invalid state");
                }

                mClient->Connect(host, port);
            }

            void UdpClient::Close()
            {
                if (!mClient) {
                    throw null_pointer("UdpClient is in an invalid state");
                }

                mClient->Close();
            }

            vector<uint8_t> UdpClient::Receive(shared_ptr<IPEndPoint>& ep)
            {
                if (!mClient) {
                    throw null_pointer("UdpClient is in an invalid state");
                }

                vector<uint8_t> vec(Available());
                mClient->ReceiveFrom(vec, ep);
                return vec;
            }

            int UdpClient::Send(const vector<uint8_t>& buffer, size_t bytes)
            {
                if (!mClient) {
                    throw null_pointer("UdpClient is in an invalid state");
                }

                return mClient->Send(buffer, 0, bytes);
            }

            int UdpClient::Send(const vector<uint8_t>& buffer, size_t bytes, shared_ptr<IPEndPoint> ep)
            {
                if (!mClient) {
                    throw null_pointer("UdpClient is in an invalid state");
                } else if (mClient->IsConnected()) {
                    throw socket_error("client is already connected");
                }

                return mClient->SendTo(buffer, 0, bytes, ep);
            }

            int UdpClient::Send(const vector<uint8_t>& buffer, size_t bytes, const String& hostname, uint16_t port)
            {
                if (!mClient) {
                    throw null_pointer("UdpClient is in an invalid state");
                } else if (mClient->IsConnected()) {
                    throw socket_error("client is already connected");
                }

                return mClient->SendTo(buffer, 0, bytes, make_shared<IPEndPoint>(IPAddress::Parse(hostname), port));
            }
        }
    }
}
