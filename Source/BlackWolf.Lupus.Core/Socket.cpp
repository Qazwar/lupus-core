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
#include "Socket.h"
#include "SocketInformation.h"
#include "NetUtility.h"
#include "IPAddress.h"
#include "IPEndPoint.h"
#include "NetDefinitions.h"

namespace Lupus {
    namespace Net {
        namespace Sockets {
            Socket::Socket(const SocketInformation& socketInformation)
            {
                if (socketInformation.ProtocolInformation.size() != sizeof(AddrStorage) + 12) {
                    throw InvalidArgument("socketInformatoin has not the right size");
                }

                Vector<uint8_t> information = socketInformation.ProtocolInformation;
                int family = *((int*)(information.data()));
                int type = *((int*)(information.data() + 4));
                int protocol = *((int*)(information.data() + 8));
                AddrStorage storage;
                int addrsize = 0;

                memset(&storage, 0, sizeof(storage));
                memcpy(&storage, socketInformation.ProtocolInformation.data() + 12, sizeof(storage));

                if ((mHandle = socket((int)family, (int)type, (int)protocol)) == INVALID_SOCKET) {
                    throw SocketError(GetLastSocketErrorString());
                }

                switch (family) {
                    case AF_INET:
                        addrsize = sizeof(AddrIn);
                        break;

                    case AF_INET6:
                        addrsize = sizeof(AddrIn6);
                        break;

                    default:
                        throw InvalidArgument("Address family is not supported");
                }

                switch (socketInformation.Options) {
                    case SocketInformationOption::Connected:
                        if (connect(mHandle, (Addr*)&storage, addrsize) != 0) {
                            throw SocketError(GetLastSocketErrorString());
                        }

                        mState.reset(new SocketConnected(this));
                        break;

                    case SocketInformationOption::Bound:
                        if (bind(mHandle, (Addr*)&storage, addrsize) != 0) {
                            throw SocketError(GetLastSocketErrorString());
                        }

                        mState.reset(new SocketBound(this));
                        break;

                    default:
                        mState.reset(new SocketReady(this));
                        break;
                }
            }

            Socket::Socket(AddressFamily family, SocketType type, ProtocolType protocol)
            {
                if ((mHandle = socket((int)family, (int)type, (int)protocol)) == INVALID_SOCKET) {
                    throw SocketError(GetLastSocketErrorString());
                }

                mState.reset(new SocketReady(this));
            }

            Socket::~Socket()
            {
                if (mHandle != INVALID_SOCKET) {
                    closesocket(mHandle);
                    mHandle = INVALID_SOCKET;
                }
            }

            Pointer<Socket> Socket::Accept()
            {
                return mState->Accept(this);
            }

            void Socket::Bind(Pointer<IPEndPoint> localEndPoint)
            {
                mState->Bind(this, localEndPoint);
            }

            void Socket::Close()
            {
                mState->Close(this);
            }

            void Socket::Close(size_t timeout)
            {
                mState->Close(this, timeout);
            }

            void Socket::Connect(Pointer<IPEndPoint> remoteEndPoint)
            {
                mState->Connect(this, remoteEndPoint);
            }

            void Socket::Connect(Pointer<IPAddress> address, uint16_t port)
            {
                mState->Connect(this, IPEndPointPtr(new IPEndPoint(address, port)));
            }

            void Socket::Connect(const Vector<Pointer<IPEndPoint>>& endPoints)
            {
                for (const IPEndPointPtr& endPoint : endPoints) {
                    try {
                        mState->Connect(this, endPoint);
                        break;
                    } catch (SocketErrorCode&) {
                        continue;
                    }
                }

                if (!IsConnected()) {
                    throw SocketError("Could not connect to given end points");
                }
            }

            void Socket::Connect(const String& host, uint16_t port)
            {
                mState->Connect(this, IPEndPointPtr(new IPEndPoint(IPAddress::Parse(host), port)));
            }

            SocketInformation Socket::DuplicateAndClose()
            {
                return mState->DuplicateAndClose(this);
            }

            void Socket::Listen(size_t backlog)
            {
                mState->Listen(this, backlog);
            }

            SocketPollFlags Socket::Poll(size_t milliSeconds, SocketPollFlags mode)
            {
                pollfd fd = { mHandle, (short)mode, 0 };
                pollfd fdarray[] = { fd };

                switch (poll(fdarray, 1, (int)milliSeconds)) {
                    case SOCKET_ERROR: throw SocketError(GetLastSocketErrorString());
                    case 0: return SocketPollFlags::Timeout;
                    default: return (SocketPollFlags)fdarray[0].revents;
                }
            }

            int Socket::Receive(Vector<uint8_t>& buffer)
            {
                SocketErrorCode errorCode;
                return mState->Receive(this, buffer, 0, (size_t)buffer.size(), SocketFlags::None, errorCode);
            }

            int Socket::Receive(Vector<uint8_t>& buffer, size_t offset)
            {
                SocketErrorCode errorCode;
                return mState->Receive(this, buffer, offset, (size_t)buffer.size() - offset, SocketFlags::None, errorCode);
            }

            int Socket::Receive(Vector<uint8_t>& buffer, size_t offset, size_t size)
            {
                SocketErrorCode errorCode;
                return mState->Receive(this, buffer, offset, size, SocketFlags::None, errorCode);
            }

            int Socket::Receive(Vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags)
            {
                SocketErrorCode errorCode;
                return mState->Receive(this, buffer, offset, size, socketFlags, errorCode);
            }

            int Socket::Receive(Vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, SocketErrorCode& errorCode)
            {
                return mState->Receive(this, buffer, offset, size, socketFlags, errorCode);
            }

            int Socket::ReceiveFrom(Vector<uint8_t>& buffer, Pointer<IPEndPoint>& remoteEndPoint)
            {
                return mState->ReceiveFrom(this, buffer, 0, (size_t)buffer.size(), SocketFlags::None, remoteEndPoint);
            }

            int Socket::ReceiveFrom(Vector<uint8_t>& buffer, size_t offset, Pointer<IPEndPoint>& remoteEndPoint)
            {
                return mState->ReceiveFrom(this, buffer, offset, (size_t)buffer.size() - offset, SocketFlags::None, remoteEndPoint);
            }

            int Socket::ReceiveFrom(Vector<uint8_t>& buffer, size_t offset, size_t size, Pointer<IPEndPoint>& remoteEndPoint)
            {
                return mState->ReceiveFrom(this, buffer, offset, size, SocketFlags::None, remoteEndPoint);
            }

            int Socket::ReceiveFrom(Vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, Pointer<IPEndPoint>& remoteEndPoint)
            {
                return mState->ReceiveFrom(this, buffer, offset, size, socketFlags, remoteEndPoint);
            }

            int Socket::Send(const Vector<uint8_t>& buffer)
            {
                SocketErrorCode errorCode;
                return mState->Send(this, buffer, 0, (size_t)buffer.size(), SocketFlags::None, errorCode);
            }

            int Socket::Send(const Vector<uint8_t>& buffer, size_t offset)
            {
                SocketErrorCode errorCode;
                return mState->Send(this, buffer, offset, (size_t)buffer.size() - offset, SocketFlags::None, errorCode);
            }

            int Socket::Send(const Vector<uint8_t>& buffer, size_t offset, size_t size)
            {
                SocketErrorCode errorCode;
                return mState->Send(this, buffer, offset, size, SocketFlags::None, errorCode);
            }

            int Socket::Send(const Vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags)
            {
                SocketErrorCode errorCode;
                return mState->Send(this, buffer, offset, size, socketFlags, errorCode);
            }

            int Socket::Send(const Vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, SocketErrorCode& errorCode)
            {
                return mState->Send(this, buffer, offset, size, socketFlags, errorCode);
            }

            int Socket::SendTo(const Vector<uint8_t>& buffer, Pointer<IPEndPoint> remoteEndPoint)
            {
                return mState->SendTo(this, buffer, 0, (size_t)buffer.size(), SocketFlags::None, remoteEndPoint);
            }

            int Socket::SendTo(const Vector<uint8_t>& buffer, size_t offset, Pointer<IPEndPoint> remoteEndPoint)
            {
                return mState->SendTo(this, buffer, offset, (size_t)buffer.size() - offset, SocketFlags::None, remoteEndPoint);
            }

            int Socket::SendTo(const Vector<uint8_t>& buffer, size_t offset, size_t size, Pointer<IPEndPoint> remoteEndPoint)
            {
                return mState->SendTo(this, buffer, offset, size, SocketFlags::None, remoteEndPoint);
            }

            int Socket::SendTo(const Vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, Pointer<IPEndPoint> remoteEndPoint)
            {
                return mState->SendTo(this, buffer, offset, size, socketFlags, remoteEndPoint);
            }

            void Socket::Shutdown(SocketShutdown how)
            {
                mState->Shutdown(this, how);
            }

            SocketHandle Socket::Handle() const
            {
                return mHandle;
            }

            bool Socket::IsConnected() const
            {
                return mConnected;
            }

            bool Socket::IsBound() const
            {
                return mBound;
            }

            bool Socket::IsListening() const
            {
                int result, length = 4;

                if (getsockopt(mHandle, SOL_SOCKET, SO_ACCEPTCONN, (char*)&result, (int*)&length) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }

                return (result == 1);
            }

            AddressFamily Socket::Family() const
            {
                return (AddressFamily)GetSocketDomain(mHandle);
            }

            ProtocolType Socket::Protocol() const
            {
                return (ProtocolType)GetSocketProtocol(mHandle);
            }

            SocketType Socket::Type() const
            {
                int result, length = 4;

                if (getsockopt(mHandle, SOL_SOCKET, SO_TYPE, (char*)&result, (int*)&length) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }

                return (SocketType)result;
            }

            size_t Socket::Available() const
            {
                u_long arg = 0;

                if (ioctlsocket(mHandle, FIONREAD, &(arg)) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }

                return (size_t)arg;
            }

            bool Socket::Blocking() const
            {
                return mBlocking;
            }

            void Socket::Blocking(bool value)
            {
                u_long arg = value ? 1 : 0;
                mBlocking = value;

                if (ioctlsocket(mHandle, FIONBIO, &(arg)) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }
            }

            LingerOption Socket::LingerState() const
            {
                LingerOption o;
                linger l;
                int s = sizeof(linger);

                if (getsockopt(mHandle, SOL_SOCKET, SO_LINGER, (char*)&l, &s) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }

                o.Enabled = l.l_onoff != 0;
                o.LingerTime = (int)l.l_linger;
                return o;
            }

            void Socket::LingerState(const LingerOption& o)
            {
                linger l;
                l.l_onoff = o.Enabled ? 1 : 0;
                l.l_linger = static_cast<decltype(l.l_linger)>(o.LingerTime);

                if (setsockopt(mHandle, SOL_SOCKET, SO_LINGER, (char*)&l, sizeof(linger)) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }
            }

            bool Socket::NoDelay() const
            {
                int result, length = 4;

                if (getsockopt(mHandle, IPPROTO_TCP, TCP_NODELAY, (char*)&result, (int*)&length) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }

                return (result != 0);
            }

            void Socket::NoDelay(bool value)
            {
                int val = value ? 1 : 0;

                if (setsockopt(mHandle, IPPROTO_TCP, TCP_NODELAY, (char*)&val, 4) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }
            }

            Pointer<IPEndPoint> Socket::LocalEndPoint() const
            {
                return mLocal;
            }

            Pointer<IPEndPoint> Socket::RemoteEndPoint() const
            {
                return mRemote;
            }

            int Socket::SendBuffer() const
            {
                int result, length = 4;

                if (getsockopt(mHandle, SOL_SOCKET, SO_SNDBUF, (char*)&result, (int*)&length) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }

                return result;
            }

            void Socket::SendBuffer(int value)
            {
                if (setsockopt(mHandle, SOL_SOCKET, SO_SNDBUF, (char*)&value, 4) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }
            }

            int Socket::ReceiveBuffer() const
            {
                int result, length = 4;

                if (getsockopt(mHandle, SOL_SOCKET, SO_RCVBUF, (char*)&result, (int*)&length) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }

                return result;
            }

            void Socket::ReceiveBuffer(int value)
            {
                if (setsockopt(mHandle, SOL_SOCKET, SO_RCVBUF, (char*)&value, 4) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }
            }

            int Socket::SendTimeout() const
            {
                return mSendTime;
            }

            void Socket::SendTimeout(int value)
            {
                if (setsockopt(mHandle, SOL_SOCKET, SO_SNDTIMEO, (char*)&value, 4) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }

                mSendTime = value;
            }

            int Socket::ReceiveTimeout() const
            {
                return mRecvTime;
            }

            void Socket::ReceiveTimeout(int value)
            {
                if (setsockopt(mHandle, SOL_SOCKET, SO_RCVTIMEO, (char*)&value, 4) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }

                mRecvTime = value;
            }

            void Socket::Select(const Vector<Pointer<Socket>>& checkRead, const Vector<Pointer<Socket>>& checkWrite, const Vector<Pointer<Socket>>& checkError, size_t microSeconds)
            {
                throw SocketError("Select is not implemented");
            }


#ifdef _MSC_VER

            int Socket::GetSocketDomain(SocketHandle h) const throw(SocketError)
            {
                WSAPROTOCOL_INFO info;
                int size = sizeof(info);

                memset(&info, 0, sizeof(WSAPROTOCOL_INFO));

                if (getsockopt(h, SOL_SOCKET, SO_PROTOCOL_INFO, (char*)&info, &size) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }

                return info.iAddressFamily;
            }

            int Socket::GetSocketProtocol(SocketHandle h) const throw(SocketError)
            {
                WSAPROTOCOL_INFO info;
                int size = sizeof(info);

                memset(&info, 0, sizeof(WSAPROTOCOL_INFO));

                if (getsockopt(h, SOL_SOCKET, SO_PROTOCOL_INFO, (char*)&info, (int*)&size) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }

                return info.iProtocol;
            }

#else

            int Socket::GetSocketDomain(SocketHandle h) const throw(SocketError)
            {
                int domain = 0;
                socklen_t size = sizeof(int);

                if (getsockopt(h, SOL_SOCKET, SO_DOMAIN, &domain, &size) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }

                return domain;
            }

            int Socket::GetSocketProtocol(SocketHandle h) const throw(SocketError)
            {
                int protocol = 0;
                socklen_t size = sizeof(int);

                if (getsockopt(h, SOL_SOCKET, SO_PROTOCOL, &protocol, &size) != 0) {
                    throw SocketError(GetLastSocketErrorString());
                }

                return protocol;
            }

#endif
        }
    }
}
