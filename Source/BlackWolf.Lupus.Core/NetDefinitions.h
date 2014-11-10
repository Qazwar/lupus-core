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
#pragma once

#include "String.h"

#ifdef _MSC_VER

#include <WinSock2.h> // Header muss vor <Windows.h> inkludiert werden
#include <WS2tcpip.h> // Header muss vor <Windows.h> inkludiert werden

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#define inet_pton InetPton
#define inet_ntop InetNtop
#define poll WSAPoll

#define LU_POLLIN POLLRDNORM
#define LU_POLLOUT POLLWRNORM
#define LU_POLLPRI POLLRDBAND

#define LU_SHUTDOWN_READ SD_RECEIVE
#define LU_SHUTDOWN_WRITE SD_SEND
#define LU_SHUTDOWN_BOTH SD_BOTH

namespace Lupus {
    namespace Net {
        namespace Sockets {
            typedef SOCKET SocketHandle;

            inline std::string GetLastSocketErrorString() {
                return std::to_string(WSAGetLastError());
            }

            inline std::string GetLastAddressInfoErrorString() {
                return std::to_string(WSAGetLastError());
            }
        }
    }
}

#else

#include <cerrno>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>

#define closesocket close
#define ioctlsocket ioctl
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#define LU_POLLIN POLLIN
#define LU_POLLOUT POLLOUT
#define LU_POLLPRI POLLPRI

#define LU_SHUTDOWN_READ SHUT_RD
#define LU_SHUTDOWN_WRITE SHUT_WR
#define LU_SHUTDOWN_BOTH SHUT_RDWR

#define GetLastSocketErrorString (std::strerror(errno))
#define GetLastAddressInfoErrorString (gai_strerror(errno))


namespace Lupus {
    namespace Net {
        namespace Sockets {
            typedef int SocketHandle;
            typedef unsigned long u_long;

            inline std::string GetLastSocketErrorString() {
                return strerror(errno);
            }

            inline std::string GetLastAddressInfoErrorString() {
                return gai_strerror(errno);
            }
        }
    }
}

#if defined(__linux__)

#include <endian.h>

#elif defined(__FreeBSD__) || defined(__NetBSD__)

#include <sys/endian.h>

#elif defined(__OpenBSD__)

#define be16toh(x) betoh16(x)
#define be32toh(x) betoh32(x)
#define be64toh(x) betoh64(x)

#endif

#define ntohll be64toh
#define htonll htobe64

#endif

namespace Lupus {
    namespace Net {
        namespace Sockets {
            typedef socklen_t AddrLength;
            typedef addrinfo AddrInfo;
            typedef sockaddr Addr;
            typedef sockaddr_in AddrIn;
            typedef sockaddr_in6 AddrIn6;
            typedef sockaddr_storage AddrStorage;
        }
    }
}
