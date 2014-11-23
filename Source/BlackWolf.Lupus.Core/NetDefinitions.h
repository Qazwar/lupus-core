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
            LUPUSCORE_API std::string GetLastSocketErrorString();
            LUPUSCORE_API std::string GetLastAddressInfoErrorString();
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
            typedef SOCKET SocketHandle;
            LUPUSCORE_API std::string GetLastSocketErrorString();
            LUPUSCORE_API std::string GetLastAddressInfoErrorString();
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
