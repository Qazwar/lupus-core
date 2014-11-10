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

#include "Task.h"
#include "HttpContext.h"
#include "String.h"
#include <memory>
#include <boost/noncopyable.hpp>

namespace Lupus {
    namespace Net {
        namespace Sockets {
            class IPEndPoint;
            class TcpListener;
            class IPAddress;
        }

        class LUPUSCORE_API HttpListener : public boost::noncopyable
        {
        public:

            HttpListener() = delete;
            HttpListener(std::shared_ptr<Sockets::TcpListener> listener);
            HttpListener(std::shared_ptr<Sockets::IPEndPoint> localEP);
            HttpListener(std::shared_ptr<Sockets::IPAddress> localaddr, uint16_t port);
            virtual ~HttpListener();

            virtual bool IsListening() const;

            virtual void Abort();
            virtual void Close();
            virtual void Start();
            virtual void Stop();

            virtual HttpContext GetContext();
            virtual Task<HttpContext> GetContextAsync();

        private:

            bool mListening = false;
            std::shared_ptr<Sockets::TcpListener> mListener;
        };
    }
}
