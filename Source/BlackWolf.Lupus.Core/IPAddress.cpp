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
#include "IPAddress.h"
#include "NetUtility.h"

namespace Lupus {
    namespace Net {
        namespace Sockets {
            IPAddress::IPAddress(U32 ipv4) :
                mFamily(AddressFamily::InterNetwork)
            {
                ipv4 = HostToNetworkOrder(ipv4);
                mAddress.insert(End(mAddress), (U8*)&ipv4, (U8*)&ipv4 + 4);
            }

            IPAddress::IPAddress(const Vector<U8>& ipv6) :
                IPAddress(ipv6, 0)
            {
            }

            IPAddress::IPAddress(const Vector<U8>& ipv6, U32 scopeid) :
                mFamily(AddressFamily::InterNetworkV6)
            {
                if (ipv6.size() != 16) {
                    throw std::length_error("std::vector must have exactly 16 bytes");
                }

                mAddress = ipv6;
                mScopeId = scopeid;
            }

            IPAddress::IPAddress(std::initializer_list<U8> ilist) :
                IPAddress(Vector<U8>(ilist))
            {
            }

            Vector<U8> IPAddress::Bytes() const
            {
                return mAddress;
            }

            AddressFamily IPAddress::Family() const
            {
                return mFamily;
            }

            bool IPAddress::IsIPv6LinkLocal() const
            {
                return false;
            }

            bool IPAddress::IsIPv6Multicast() const
            {
                return false;
            }

            bool IPAddress::IsIPv6SiteLocal() const
            {
                return false;
            }

            U32 IPAddress::ScopeId() const
            {
                return mScopeId;
            }

            void IPAddress::ScopeId(U32 value)
            {
                mScopeId = value;
            }

            String IPAddress::ToString() const
            {
                in_addr addr;
                in6_addr addr6;
#ifdef _UNICODE
                wchar_t str[INET6_ADDRSTRLEN];
                wmemset(str, 0, INET6_ADDRSTRLEN);

#else
                char str[INET6_ADDRSTRLEN];
                memset(str, 0, INET6_ADDRSTRLEN);
#endif
                memset(&addr, 0, sizeof(in_addr));
                memset(&addr6, 0, sizeof(in6_addr));

                switch (Family()) {
                    case AddressFamily::InterNetwork:
                        memcpy(&addr, Bytes().data(), 4);
                        inet_ntop(AF_INET, &addr, str, INET6_ADDRSTRLEN);
                        break;

                    case AddressFamily::InterNetworkV6:
                        memcpy(&addr6, Bytes().data(), 16);
                        inet_ntop(AF_INET6, &addr6, str, INET6_ADDRSTRLEN);
                        break;
                }

                return str;
            }

            bool IPAddress::IsLoopback(Pointer<IPAddress> address)
            {
                Vector<U8> addressBytes = address->Bytes();
                Vector<U8> comparer;

                switch (address->Family()) {
                    case AddressFamily::InterNetwork:
                        comparer = IPAddress::Loopback()->Bytes();

                        for (U32 i = 0; i < comparer.size(); i++) {
                            if (addressBytes[i] != comparer[i]) {
                                return false;
                            }
                        }

                        break;

                    case AddressFamily::InterNetworkV6:
                        comparer = IPAddress::IPv6Loopback()->Bytes();

                        for (U32 i = 0; i < comparer.size(); i++) {
                            if (addressBytes[i] != comparer[i]) {
                                return false;
                            }
                        }

                        break;
                }

                return true;
            }

            Pointer<IPAddress> IPAddress::Parse(const String& ipString)
            {
                IPAddress* address = new IPAddress(0);
                AddrIn addr;
                AddrIn6 addr6;

                memset(&addr, 0, sizeof(AddrIn));
                memset(&addr6, 0, sizeof(AddrIn6));
                address->mAddress.clear();

#ifdef _UNICODE
                if (inet_pton(AF_INET, ipString.Data(), &(addr.sin_addr)) == 1) {
                    address = new IPAddress(NetworkToHostOrder(*((U32*)&addr.sin_addr)));
                } else if (inet_pton(AF_INET6, ipString.Data(), &(addr6.sin6_addr)) == 1) {
                    U8* Begin = (U8*)&addr6.sin6_addr;
                    address = new IPAddress(0);
                    address->mAddress.clear();
                    address->mAddress.reserve(16);

                    for (int i = 0; i < 16; i++) { // Konvertiere von Netzwerk zu Host.
                        address->mAddress.push_back(*(Begin + i));
                    }
                } else {
                    throw InvalidArgument("Not a valid IP address presentation");
                }
#else
                if (inet_pton(AF_INET, ipString.ToUTF8().c_str(), &(addr.sin_addr)) == 1) {
                    address = new IPAddress(NetworkToHostOrder(*((U32*)&addr.sin_addr)));
                } else if (inet_pton(AF_INET6, ipString.ToUTF8().c_str(), &(addr6.sin6_addr)) == 1) {
                    U8* Begin = (U8*)&addr6.sin6_addr;
                    address = new IPAddress(0);
                    address->mAddress.clear();
                    address->mAddress.reserve(16);

                    for (int i = 0; i < 16; i++) { // Konvertiere von Netzwerk zu Host.
                        address->mAddress.push_back(*(Begin + i));
                    }
                } else {
                    throw InvalidArgument("Not a valid IP address presentation");
                }
#endif

                return Pointer<IPAddress>(address);
            }

            bool IPAddress::TryParse(const String& ipString, Pointer<IPAddress>& address)
            {
                try {
                    address = IPAddress::Parse(ipString);
                } catch (InvalidArgument&) {
                    return false;
                }

                return true;
            }

            Pointer<IPAddress> IPAddress::Any()
            {
                return sAny;
            }

            Pointer<IPAddress> IPAddress::Broadcast()
            {
                return sBroadcast;
            }

            Pointer<IPAddress> IPAddress::IPv6Any()
            {
                return sIPv6Any;
            }

            Pointer<IPAddress> IPAddress::IPv6Loopback()
            {
                return sIPv6Loopback;
            }

            Pointer<IPAddress> IPAddress::IPv6None()
            {
                return sIPv6None;
            }

            Pointer<IPAddress> IPAddress::Loopback()
            {
                return sLoopback;
            }

            Pointer<IPAddress> IPAddress::None()
            {
                return sNone;
            }

            const Pointer<IPAddress> IPAddress::sAny(new IPAddress(0));
            const Pointer<IPAddress> IPAddress::sBroadcast(new IPAddress(0xFFFFFFFF));
            const Pointer<IPAddress> IPAddress::sIPv6Any(new IPAddress(Vector<U8>({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 })));
            const Pointer<IPAddress> IPAddress::sIPv6Loopback(new IPAddress(Vector<U8>({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01 })));
            const Pointer<IPAddress> IPAddress::sIPv6None(new IPAddress(Vector<U8>({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 })));
            const Pointer<IPAddress> IPAddress::sLoopback(new IPAddress(0x7F000001));
            const Pointer<IPAddress> IPAddress::sNone(new IPAddress(0));
        }
    }
}
