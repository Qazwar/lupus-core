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
#include "Socket.h"
#include "IPAddress.h"
#include "IPEndPoint.h"
#include "SocketInformation.h"

#include <thread>

namespace Lupus {
    namespace Net {
        namespace Sockets {
            std::shared_ptr<Socket> Socket::SocketState::Accept(Socket* socket)
            {
                throw socket_error("Socket is not in an valid state for Accept");
            }

            void Socket::SocketState::Bind(Socket* socket, std::shared_ptr<IPEndPoint> localEndPoint)
            {
                throw socket_error("Socket is not in an valid state for Bind");
            }

            void Socket::SocketState::Close(Socket* socket)
            {
                if (socket->Handle() != INVALID_SOCKET) {
                    if (closesocket(socket->Handle()) != 0) {
                        throw socket_error(GetLastSocketErrorString());
                    }

                    socket->mHandle = INVALID_SOCKET;
                    socket->mSendTime = 0;
                    socket->mRecvTime = 0;
                    socket->mBlocking = true;
                    socket->mLocal = IPEndPointPtr(nullptr);
                    socket->mRemote = IPEndPointPtr(nullptr);
                    socket->mBound = false;
                    socket->mConnected = false;

                    ChangeState(socket, std::shared_ptr<Socket::SocketState>(new SocketClosed()));
                } else {
                    return ChangeState(socket, std::shared_ptr<Socket::SocketState>(new SocketClosed()));
                }
            }

            void Socket::SocketState::Close(Socket* socket, size_t timeout)
            {
                if (socket->Handle() == INVALID_SOCKET) {
                    return ChangeState(socket, std::shared_ptr<Socket::SocketState>(new SocketClosed()));
                } else {
                    socket->LingerState({ true, (int)timeout });
                    this->Close(socket);
                }
            }

            void Socket::SocketState::Connect(Socket* socket, std::shared_ptr<IPEndPoint> remoteEndPoint)
            {
                throw socket_error("Socket is not in an valid state for Connect");
            }

            SocketInformation Socket::SocketState::DuplicateAndClose(Socket* socket)
            {
                IPEndPointPtr point;
                int family = (int)socket->Family();
                int type = (int)socket->Type();
                int protocol = (int)socket->Protocol();
                SocketInformation info = {
                    SocketInformationOption::None,
                    std::vector<uint8_t>()
                };

                if (!socket->mLocal && !socket->mRemote) {
                    throw null_pointer("Socket endpoint points to NULL");
                } else if (!socket->mLocal) {
                    point = socket->mRemote;
                } else {
                    point = socket->mLocal;
                }

                info.ProtocolInformation.insert(std::end(info.ProtocolInformation), (uint8_t*)&family, (uint8_t*)&family + 4);
                info.ProtocolInformation.insert(std::end(info.ProtocolInformation), (uint8_t*)&type, (uint8_t*)&type + 4);
                info.ProtocolInformation.insert(std::end(info.ProtocolInformation), (uint8_t*)&protocol, (uint8_t*)&protocol + 4);

                if (socket->IsBound()) {
                    std::vector<uint8_t> bytes = point->Address()->Bytes();
                    info.Options = SocketInformationOption::Bound;
                    info.ProtocolInformation.insert(std::end(info.ProtocolInformation), std::begin(bytes), std::end(bytes));
                } else if (socket->IsConnected()) {
                    std::vector<uint8_t> bytes = socket->mRemote->Address()->Bytes();
                    info.Options = SocketInformationOption::Connected;
                    info.ProtocolInformation.insert(std::end(info.ProtocolInformation), std::begin(bytes), std::end(bytes));
                } else {
                    info.ProtocolInformation.resize(info.ProtocolInformation.size() + sizeof(AddrStorage));
                }

                Close(socket);
                return info;
            }

            void Socket::SocketState::Listen(Socket* socket, size_t backlog)
            {
                throw socket_error("Socket is not bound to an end point");
            }

            int Socket::SocketState::Receive(Socket* socket, std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, SocketError& errorCode)
            {
                throw socket_error("Socket is not in an valid state for Receive");
            }

            int Socket::SocketState::ReceiveFrom(Socket* socket, std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, std::shared_ptr<IPEndPoint>& remoteEndPoint)
            {
                if (offset > buffer.size()) {
                    throw std::out_of_range("offset");
                } else if (size > buffer.size() - offset) {
                    throw std::out_of_range("size");
                }

                int result = 0;
                AddrStorage storage;
                AddrLength length = sizeof(AddrStorage);

                memset(&storage, 0, sizeof(AddrStorage));
                result = recvfrom(socket->Handle(), (char*)buffer.data() + offset, (int)size, (int)socketFlags, (Addr*)&storage, &length);
                remoteEndPoint = IPEndPointPtr(new IPEndPoint(std::vector<uint8_t>((uint8_t*)&storage, (uint8_t*)&storage + sizeof(AddrLength))));
                return result;
            }

            int Socket::SocketState::Send(Socket* socket, const std::vector<uint8_t>& buaffer, size_t offset, size_t size, SocketFlags socketFlags, SocketError& errorCode)
            {
                throw socket_error("Socket is not in an valid state for Send");
            }

            int Socket::SocketState::SendTo(Socket* socket, const std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, std::shared_ptr<IPEndPoint> remoteEndPoint)
            {
                if (offset > buffer.size()) {
                    throw std::out_of_range("offset");
                } else if (size > buffer.size() - offset) {
                    throw std::out_of_range("size");
                }

                std::vector<uint8_t> address = remoteEndPoint->Serialize();

                return sendto(socket->Handle(), (const char*)buffer.data() + offset, (int)size, (int)socketFlags, (const Addr*)address.data(), (int)buffer.size());
            }

            void Socket::SocketState::Shutdown(Socket* socket, SocketShutdown how)
            {
                throw socket_error("Socket is not in an valid state for Shutdown");
            }

            std::shared_ptr<Socket> Socket::SocketState::CreateSocket(Socket* socket, SocketHandle h, AddrStorage s)
            {
                Socket* sock = new Socket();
                sock->mHandle = h;
                sock->mConnected = true;
                sock->mLocal = socket->LocalEndPoint();
                sock->mRemote = IPEndPointPtr(new IPEndPoint(std::vector<uint8_t>((uint8_t*)&s, (uint8_t*)&s + sizeof(AddrStorage))));
                sock->mState = std::shared_ptr<Socket::SocketState>(new Socket::SocketConnected(sock));
                return SocketPtr(sock);
            }

            void Socket::SocketState::ChangeState(Socket* socket, std::shared_ptr<Socket::SocketState> state)
            {
                socket->mState = state;
            }

            void Socket::SocketState::SetLocalEndPoint(Socket* socket, std::shared_ptr<IPEndPoint> remote)
            {
                socket->mLocal = remote;
            }

            void Socket::SocketState::SetRemoteEndPoint(Socket* socket, std::shared_ptr<IPEndPoint> remote)
            {
                socket->mRemote = remote;
            }

            std::shared_ptr<IPEndPoint> Socket::SocketState::GetLocalEndPoint(Socket* socket) const
            {
                return socket->mLocal;
            }

            std::shared_ptr<IPEndPoint> Socket::SocketState::GetRemoteEndPoint(Socket* socket) const
            {
                return socket->mRemote;
            }

            void Socket::SocketState::SetConnected(Socket* socket, bool value)
            {
                socket->mConnected = value;
            }

            void Socket::SocketState::SetBound(Socket* socket, bool value)
            {
                socket->mBound = value;
            }

            Socket::SocketBound::SocketBound(Socket* socket)
            {
                SetBound(socket, true);
            }

            Socket::SocketBound::SocketBound(Socket* socket, std::shared_ptr<IPEndPoint> endPoint)
            {
                SetBound(socket, true);
                SetLocalEndPoint(socket, endPoint);
            }

            void Socket::SocketBound::Connect(Socket* socket, std::shared_ptr<IPEndPoint> remoteEndPoint)
            {
                if (!remoteEndPoint) {
                    throw null_pointer("remoteEndPoint");
                }

                AddrStorage storage;

                memset(&storage, 0, sizeof(AddrStorage));
                memcpy(&storage, remoteEndPoint->Serialize().data(), sizeof(AddrStorage));

                if (connect(socket->Handle(), (Addr*)&storage, sizeof(AddrStorage)) != 0) {
                    throw socket_error(GetLastSocketErrorString());
                }

                ChangeState(socket, std::shared_ptr<Socket::SocketState>(new Socket::SocketConnected(socket)));
            }

            void Socket::SocketBound::Listen(Socket* socket, size_t backlog)
            {
                if (listen(socket->Handle(), (int)backlog) != 0) {
                    throw socket_error(GetLastSocketErrorString());
                }

                ChangeState(socket, std::shared_ptr<Socket::SocketState>(new Socket::SocketListen(socket)));
            }

            Socket::SocketListen::SocketListen(Socket* s)
            {
                SetConnected(s, false);
                SetBound(s, true);
            }

            std::shared_ptr<Socket> Socket::SocketListen::Accept(Socket* socket)
            {
                SocketHandle handle;
                AddrStorage storage;
                AddrLength length = sizeof(AddrStorage);

                memset(&storage, 0, sizeof(AddrStorage));

                if ((handle = accept(socket->Handle(), (Addr*)&storage, &length)) == INVALID_SOCKET) {
                    throw socket_error(GetLastSocketErrorString());
                }

                return CreateSocket(socket, handle, storage);
            }

            Socket::SocketConnected::SocketConnected(Socket* s)
            {
                SetConnected(s, true);
            }

            Socket::SocketConnected::SocketConnected(Socket* s, std::shared_ptr<IPEndPoint> p)
            {
                SetConnected(s, true);
                SetRemoteEndPoint(s, p);
            }

            void Socket::SocketConnected::Connect(Socket* socket, std::shared_ptr<IPEndPoint> remoteEndPoint)
            {
                if (!remoteEndPoint) {
                    throw null_pointer("remoteEndPoint");
                }

                AddrStorage storage;

                memset(&storage, 0, sizeof(AddrStorage));
                memcpy(&storage, remoteEndPoint->Serialize().data(), sizeof(AddrStorage));

                if (connect(socket->Handle(), (Addr*)&storage, sizeof(AddrStorage)) != 0) {
                    throw socket_error(GetLastSocketErrorString());
                }
            }

            int Socket::SocketConnected::Receive(Socket* socket, std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, SocketError& errorCode)
            {
                if (offset > buffer.size()) {
                    throw std::out_of_range("offset");
                } else if (size > buffer.size() - offset) {
                    throw std::out_of_range("size");
                }

                int result = recv(socket->Handle(), (char*)buffer.data() + offset, (int)size, (int)socketFlags);

                if (result < 0) {
                    errorCode = force_cast<SocketError>(result);
                }

                return result;
            }

            int Socket::SocketConnected::Send(Socket* socket, const std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, SocketError& errorCode)
            {
                if (offset > buffer.size()) {
                    throw std::out_of_range("offset");
                } else if (size > buffer.size() - offset) {
                    throw std::out_of_range("size");
                }

                int result = send(socket->Handle(), (const char*)buffer.data() + offset, (int)size, (int)socketFlags);

                if (result < 0) {
                    errorCode = force_cast<SocketError>(result);
                }

                return result;
            }

            void Socket::SocketConnected::Shutdown(Socket* socket, SocketShutdown how)
            {
                if (shutdown(socket->Handle(), (int)how) != 0) {
                    throw socket_error(GetLastSocketErrorString());
                }
            }

            Socket::SocketReady::SocketReady(Socket* s)
            {
                SetBound(s, false);
                SetConnected(s, false);
            }

            void Socket::SocketReady::Bind(Socket* socket, std::shared_ptr<IPEndPoint> localEndPoint) throw(socket_error)
            {
                int yes = 1;
                std::vector<uint8_t> address = localEndPoint->Serialize();

                if (setsockopt(socket->Handle(), SOL_SOCKET, SO_REUSEADDR, (const char*)&yes, sizeof(int)) != 0) {
                    throw socket_error(GetLastSocketErrorString());
                } else if (bind(socket->Handle(), (const Addr*)address.data(), (int)address.size()) != 0) {
                    throw socket_error(GetLastSocketErrorString());
                }

                ChangeState(socket, std::shared_ptr<Socket::SocketState>(new Socket::SocketBound(socket, localEndPoint)));
            }

            void Socket::SocketReady::Connect(Socket* socket, std::shared_ptr<IPEndPoint> remoteEndPoint) throw(socket_error, null_pointer)
            {
                ChangeState(socket, std::shared_ptr<Socket::SocketState>(new Socket::SocketConnected(socket, remoteEndPoint)));
            }

            void Socket::SocketClosed::Close(Socket* socket)
            {
                // do nothing
            }

            void Socket::SocketClosed::Close(Socket* socket, size_t timeout)
            {
                // do nothing
            }

            SocketInformation Socket::SocketClosed::DuplicateAndClose(Socket* socket)
            {
                throw socket_error("Socket is not in an valid state for DuplicateAndClose");
            }

            int Socket::SocketClosed::ReceiveFrom(Socket* socket, std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, std::shared_ptr<IPEndPoint>& remoteEndPoint)
            {
                throw socket_error("Socket is not in an valid state for ReceiveFrom");
            }

            int Socket::SocketClosed::SendTo(Socket* socket, const std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, std::shared_ptr<IPEndPoint> remoteEndPoint)
            {
                throw socket_error("Socket is not in an valid state for SendTo");
            }
        }
    }
}
