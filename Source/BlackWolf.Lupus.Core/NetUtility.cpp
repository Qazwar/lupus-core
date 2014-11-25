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
#include "NetUtility.h"
#include "IPAddress.h"
#include "IPEndPoint.h"
#include "Socket.h"

namespace Lupus {
    namespace Net {
        namespace Sockets {
            U16 HostToNetworkOrder(U16 host)
            {
                return htons(host);
            }

            U32 HostToNetworkOrder(U32 host)
            {
                return htonl(host);
            }

            U64 HostToNetworkOrder(U64 host)
            {
                return htonll(host);
            }

            U16 NetworkToHostOrder(U16 network)
            {
                return ntohs(network);
            }

            U32 NetworkToHostOrder(U32 network)
            {
                return ntohl(network);
            }

            U64 NetworkToHostOrder(U64 network)
            {
                return ntohll(network);
            }

            Vector<Pointer<IPEndPoint>> GetAddressInformation(const String& node, const String& service)
            {
                return GetAddressInformation(node, service, AddressFamily::Unspecified, SocketType::Unspecified, ProtocolType::Unspecified);
            }

            Vector<Pointer<IPEndPoint>> GetAddressInformation(const String& node, const String& service, AddressFamily family)
            {
                return GetAddressInformation(node, service, family, SocketType::Unspecified, ProtocolType::Unspecified);
            }

            Vector<Pointer<IPEndPoint>> GetAddressInformation(const String& node, const String& service, SocketType type)
            {
                return GetAddressInformation(node, service, AddressFamily::Unspecified, type, ProtocolType::Unspecified);
            }

            Vector<Pointer<IPEndPoint>> GetAddressInformation(const String& node, const String& service, ProtocolType protocol)
            {
                return GetAddressInformation(node, service, AddressFamily::Unspecified, SocketType::Unspecified, protocol);
            }

            Vector<Pointer<IPEndPoint>> GetAddressInformation(const String& node, const String& service, AddressFamily family, SocketType type, ProtocolType protocol)
            {
                if (service.IsEmpty()) {
                    throw InvalidArgument("service argument must have a valid value");
                }
#ifdef _UNICODE
                Vector<Pointer<IPEndPoint>> addresses;
                const wchar_t* nodename = node.IsEmpty() ? nullptr : node.Data();
                ADDRINFOW hints, *Begin = nullptr, *it = nullptr;

                memset(&hints, 0, sizeof(hints));
                hints.ai_family = (int)family;
                hints.ai_socktype = (int)type;
                hints.ai_protocol = (int)protocol;

                if (!nodename) {
                    hints.ai_flags = AI_PASSIVE;
                }

                if (GetAddrInfoW(nodename, service.Data(), &hints, &Begin) != 0) {
                    if (Begin) {
                        FreeAddrInfoW(Begin);
                    }

                    throw RuntimeError(GetLastAddressInfoErrorString());
                }

                for (it = Begin; it; it = it->ai_next) {
                    AddrStorage storage;

                    memset(&storage, 0, sizeof(AddrStorage));
                    memcpy(&storage, it->ai_addr, it->ai_addrlen);
                    addresses.push_back(IPEndPointPtr(new IPEndPoint(Vector<U8>((U8*)&storage, (U8*)&storage + sizeof(AddrStorage)))));
                }

                FreeAddrInfoW(Begin);
                return addresses;
#else
                Vector<Pointer<IPEndPoint>> addresses;
                const char* nodename = node.IsEmpty() ? nullptr : node.ToUTF8().c_str();
                AddrInfo hints, *Begin = nullptr, *it = nullptr;

                memset(&hints, 0, sizeof(hints));
                hints.ai_family = (int)family;
                hints.ai_socktype = (int)type;
                hints.ai_protocol = (int)protocol;

                if (!nodename) {
                    hints.ai_flags = AI_PASSIVE;
                }

                if (getaddrinfo(nodename, service.ToUTF8().c_str(), &hints, &Begin) != 0) {
                    if (Begin) {
                        freeaddrinfo(Begin);
                    }

                    throw RuntimeError(GetLastAddressInfoErrorString());
                }

                for (it = Begin; it; it = it->ai_next) {
                    AddrStorage storage;

                    memset(&storage, 0, sizeof(AddrStorage));
                    memcpy(&storage, it->ai_addr, it->ai_addrlen);
                    addresses.push_back(IPEndPointPtr(new IPEndPoint(Vector<U8>((U8*)&storage, (U8*)&storage + sizeof(AddrStorage)))));
                }

                freeaddrinfo(Begin);
                return addresses;
#endif
            }
        }
    }
}
