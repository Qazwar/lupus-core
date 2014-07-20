#include "IPAddress.h"
#include "NetUtility.h"

namespace Lupus {
    namespace Net {
        namespace Sockets {
            IPAddress::IPAddress(uint32_t ipv4) :
                mFamily(AddressFamily::InterNetwork)
            {
                ipv4 = HostToNetworkOrder(ipv4);
                mAddress.insert(std::end(mAddress), (uint8_t*)&ipv4, (uint8_t*)&ipv4 + 4);
            }

            IPAddress::IPAddress(const std::vector<uint8_t>& ipv6) :
                IPAddress(ipv6, 0)
            {
            }

            IPAddress::IPAddress(const std::vector<uint8_t>& ipv6, uint32_t scopeid) :
                mFamily(AddressFamily::InterNetworkV6)
            {
                if (ipv6.size() != 16) {
                    throw std::length_error("std::vector must have exactly 16 bytes");
                }

                mAddress = ipv6;
                mScopeId = scopeid;
            }

            IPAddress::IPAddress(std::initializer_list<uint8_t> ilist) :
                IPAddress(std::vector<uint8_t>(ilist))
            {
            }

            std::vector<uint8_t> IPAddress::Bytes() const
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

            uint32_t IPAddress::ScopeId() const
            {
                return mScopeId;
            }

            void IPAddress::ScopeId(uint32_t value)
            {
                mScopeId = value;
            }

            std::string IPAddress::ToString() const
            {
                in_addr addr;
                in6_addr addr6;
                char str[INET6_ADDRSTRLEN];

                memset(&addr, 0, sizeof(in_addr));
                memset(&addr6, 0, sizeof(in6_addr));
                memset(str, 0, INET6_ADDRSTRLEN);

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

            bool IPAddress::IsLoopback(std::shared_ptr<IPAddress> address)
            {
                std::vector<uint8_t> addressBytes = address->Bytes();
                std::vector<uint8_t> comparer;

                switch (address->Family()) {
                    case AddressFamily::InterNetwork:
                        comparer = IPAddress::Loopback()->Bytes();

                        for (size_t i = 0; i < comparer.size(); i++) {
                            if (addressBytes[i] != comparer[i]) {
                                return false;
                            }
                        }

                        break;

                    case AddressFamily::InterNetworkV6:
                        comparer = IPAddress::IPv6Loopback()->Bytes();

                        for (size_t i = 0; i < comparer.size(); i++) {
                            if (addressBytes[i] != comparer[i]) {
                                return false;
                            }
                        }

                        break;
                }

                return true;
            }

            std::shared_ptr<IPAddress> IPAddress::Parse(const std::string& ipString)
            {
                IPAddress* address = new IPAddress(0);
                AddrIn addr;
                AddrIn6 addr6;

                memset(&addr, 0, sizeof(AddrIn));
                memset(&addr6, 0, sizeof(AddrIn6));
                address->mAddress.clear();

                if (inet_pton(AF_INET, ipString.c_str(), &(addr.sin_addr)) == 1) {
                    address = new IPAddress(NetworkToHostOrder(*((uint32_t*)&addr.sin_addr)));
                } else if (inet_pton(AF_INET6, ipString.c_str(), &(addr6.sin6_addr)) == 1) {
                    uint8_t* begin = (uint8_t*)&addr6.sin6_addr;
                    address = new IPAddress(0);
                    address->mAddress.clear();
                    address->mAddress.reserve(16);

                    for (int i = 0; i < 16; i++) { // Konvertiere von Netzwerk zu Host.
                        address->mAddress.push_back(*(begin + i));
                    }
                } else {
                    throw std::invalid_argument("Not a valid IP address presentation");
                }

                return std::shared_ptr<IPAddress>(address);
            }

            bool IPAddress::TryParse(const std::string& ipString, std::shared_ptr<IPAddress>& address)
            {
                try {
                    address = IPAddress::Parse(ipString);
                } catch (std::invalid_argument&) {
                    return false;
                }

                return true;
            }

            std::shared_ptr<IPAddress> IPAddress::Any()
            {
                return sAny;
            }

            std::shared_ptr<IPAddress> IPAddress::Broadcast()
            {
                return sBroadcast;
            }

            std::shared_ptr<IPAddress> IPAddress::IPv6Any()
            {
                return sIPv6Any;
            }

            std::shared_ptr<IPAddress> IPAddress::IPv6Loopback()
            {
                return sIPv6Loopback;
            }

            std::shared_ptr<IPAddress> IPAddress::IPv6None()
            {
                return sIPv6None;
            }

            std::shared_ptr<IPAddress> IPAddress::Loopback()
            {
                return sLoopback;
            }

            std::shared_ptr<IPAddress> IPAddress::None()
            {
                return sNone;
            }

            const std::shared_ptr<IPAddress> IPAddress::sAny(new IPAddress(0));
            const std::shared_ptr<IPAddress> IPAddress::sBroadcast(new IPAddress(0xFFFFFFFF));
            const std::shared_ptr<IPAddress> IPAddress::sIPv6Any(new IPAddress(std::vector<uint8_t>({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 })));
            const std::shared_ptr<IPAddress> IPAddress::sIPv6Loopback(new IPAddress(std::vector<uint8_t>({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01 })));
            const std::shared_ptr<IPAddress> IPAddress::sIPv6None(new IPAddress(std::vector<uint8_t>({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 })));
            const std::shared_ptr<IPAddress> IPAddress::sLoopback(new IPAddress(0x7F000001));
            const std::shared_ptr<IPAddress> IPAddress::sNone(new IPAddress(0));
        }
    }
}
