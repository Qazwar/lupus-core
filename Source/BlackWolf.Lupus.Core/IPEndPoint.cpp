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
#include "IPEndPoint.h"
#include "IPAddress.h"
#include "NetUtility.h"

namespace Lupus {
    namespace Net {
        namespace Sockets {
            IPEndPoint::IPEndPoint(uint32_t address, uint16_t port) :
                IPEndPoint(std::make_shared<IPAddress>(address), port)
            {
            }

            IPEndPoint::IPEndPoint(std::shared_ptr<IPAddress> address, uint16_t port)
            {
                if (!address) {
                    throw null_pointer("address");
                }

                AddrIn* addr;
                AddrIn6* addr6;

                memset(&mAddrStorage, 0, sizeof(AddrStorage));

                switch (address->Family()) {
                    case AddressFamily::InterNetwork:
                        addr = (AddrIn*)&mAddrStorage;
                        addr->sin_family = AF_INET;
                        addr->sin_port = HostToNetworkOrder(port);
                        memcpy(&addr->sin_addr, address->Bytes().data(), 4);
                        break;

                    case AddressFamily::InterNetworkV6:
                        addr6 = (AddrIn6*)&mAddrStorage;
                        addr6->sin6_family = AF_INET;
                        addr6->sin6_port = HostToNetworkOrder(port);
                        memcpy(&addr6->sin6_addr, address->Bytes().data(), 16);
                        break;
                }

                mAddress = address;
            }

            IPEndPoint::IPEndPoint(const std::vector<uint8_t>& buffer)
            {
                if (buffer.size() != sizeof(AddrStorage)) {
                    throw std::invalid_argument("buffer contains invalid data");
                }

                memset(&mAddrStorage, 0, sizeof(AddrStorage));
                memcpy(&mAddrStorage, buffer.data(), sizeof(AddrStorage));
            }

            AddressFamily IPEndPoint::Family() const
            {
                return mAddress->Family();
            }

            std::shared_ptr<IPAddress> IPEndPoint::Address() const
            {
                return mAddress;
            }

            void IPEndPoint::Address(std::shared_ptr<IPAddress> address)
            {
                if (!address) {
                    throw null_pointer("address");
                }

                uint16_t port = Port();
                AddrIn* addr;
                AddrIn6* addr6;

                memset(&mAddrStorage, 0, sizeof(AddrStorage));

                switch (address->Family()) {
                    case AddressFamily::InterNetwork:
                        addr = (AddrIn*)&mAddrStorage;
                        addr->sin_family = AF_INET;
                        addr->sin_port = HostToNetworkOrder(port);
                        memcpy(&addr->sin_addr, address->Bytes().data(), 4);
                        break;

                    case AddressFamily::InterNetworkV6:
                        addr6 = (AddrIn6*)&mAddrStorage;
                        addr6->sin6_family = AF_INET;
                        addr6->sin6_port = HostToNetworkOrder(port);
                        memcpy(&addr6->sin6_addr, address->Bytes().data(), 16);
                        break;
                }

                mAddress = address;
            }

            uint16_t IPEndPoint::Port() const
            {
                switch (mAddrStorage.ss_family) {
                    case AF_INET:
                        return NetworkToHostOrder(((AddrIn*)&mAddrStorage)->sin_port);

                    case AF_INET6:
                        return NetworkToHostOrder(((AddrIn6*)&mAddrStorage)->sin6_port);
                }

                return 0;
            }

            void IPEndPoint::Port(uint16_t port)
            {
                switch (mAddrStorage.ss_family) {
                    case AF_INET:
                        ((AddrIn*)&mAddrStorage)->sin_port = HostToNetworkOrder(port);

                    case AF_INET6:
                        ((AddrIn6*)&mAddrStorage)->sin6_port = HostToNetworkOrder(port);
                }
            }

            std::vector<uint8_t> IPEndPoint::Serialize() const
            {
                return std::vector<uint8_t>((uint8_t*)&mAddrStorage, (uint8_t*)&mAddrStorage + sizeof(AddrStorage));
            }
        }
    }
}
