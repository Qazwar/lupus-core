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

#include <vector>
#include <memory>
#include <functional>
#include "String.h"
#include "Task.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Net {
        namespace Sockets {
            class Socket;
            class IPAddress;
            class IPEndPoint;
            class TcpClient;

            class LUPUSCORE_API TcpListener : public NonCopyable
            {
            public:

                TcpListener(std::shared_ptr<IPEndPoint> localEP) throw(socket_error, null_pointer);
                TcpListener(std::shared_ptr<IPAddress> localaddr, uint16_t port) throw(socket_error, null_pointer);
                virtual ~TcpListener() = default;

                virtual bool IsActive() const throw(socket_error);
                virtual bool ExclusiveAddressUse() const throw(socket_error);
                virtual void ExclusiveAddressUse(bool) throw(socket_error);
                virtual std::shared_ptr<IPEndPoint> LocalEndPoint() const NOEXCEPT;
                virtual std::shared_ptr<Socket> Server() const NOEXCEPT;

                virtual Task<std::shared_ptr<Socket>> AcceptSocketAsync() NOEXCEPT;
                virtual Task<std::shared_ptr<TcpClient>> AcceptTcpClientAsync() NOEXCEPT;

                virtual std::shared_ptr<Socket> AcceptSocket() throw(socket_error);
                virtual std::shared_ptr<TcpClient> AcceptTcpClient() throw(socket_error);
                virtual void Start() throw(socket_error);
                virtual void Start(int backlog) throw(socket_error);
                virtual void Stop() throw(socket_error);

            private:

                std::shared_ptr<Socket> mServer = nullptr;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
