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
#include "HttpListener.h"
#include "HttpListenerRequest.h"
#include "HttpListenerResponse.h"
#include "HttpContext.h"
#include "TcpListener.h"
#include "IPEndPoint.h"
#include "IPAddress.h"
#include "Socket.h"

using namespace std;
using namespace Lupus::Net::Sockets;

namespace Lupus {
    namespace Net {
        HttpListener::HttpListener(shared_ptr<TcpListener> listener) :
            mListener(listener)
        {
            if (!listener) {
                throw null_pointer("listener");
            } else if (!listener->IsActive()) {
                listener->Start(255);
            }
        }

        HttpListener::HttpListener(shared_ptr<IPEndPoint> localEP)
        {
            if (!localEP) {
                throw null_pointer("localEP");
            }

            mListener = make_shared<TcpListener>(localEP);
            mListener->Start(255);
        }

        HttpListener::HttpListener(shared_ptr<IPAddress> localaddr, uint16_t port)
        {
            if (!localaddr) {
                throw null_pointer("localaddr");
            }

            mListener = make_shared<TcpListener>(localaddr, port);
            mListener->Start(255);
        }

        bool HttpListener::IsListening() const
        {
            return mListening;
        }

        void HttpListener::Abort()
        {
            mListener->Server()->LingerState({ true, 0 });
            mListener->Stop();
        }

        void HttpListener::Close()
        {
            mListener->Stop();
        }

        void HttpListener::Start()
        {
            mListening = true;
        }

        void HttpListener::Stop()
        {
            mListening = false;
        }

        HttpContext HttpListener::GetContext()
        {
            if (mListening) {
                // TODO: Accept und auslesen
            }

            return{ nullptr, nullptr };
        }

        Task<HttpContext> HttpListener::GetContextAsync()
        {
            // TODO: C2512 ausbessern.
            return Task<HttpContext>([this]() {
                return this->GetContext();
            });
        }
    }
}
