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
#include "HttpListener.h"
#include "HttpListenerRequest.h"
#include "HttpListenerResponse.h"
#include "HttpContext.h"
#include "TcpListener.h"
#include "IPEndPoint.h"
#include "IPAddress.h"
#include "Socket.h"
#include "TcpClient.h"
#include "NetworkStream.h"


using namespace Lupus::Net::Sockets;

namespace Lupus {
    namespace Net {
        HttpListener::HttpListener(Pointer<TcpListener> listener) :
            mListener(listener)
        {
            if (!listener) {
                throw NullPointer("listener");
            } else if (!listener->IsActive()) {
                listener->Start(255);
            }
        }

        HttpListener::HttpListener(Pointer<IPEndPoint> localEP)
        {
            if (!localEP) {
                throw NullPointer("localEP");
            }

            mListener = MakePointer<TcpListener>(localEP);
            mListener->Start(255);
        }

        HttpListener::HttpListener(Pointer<IPAddress> localaddr, uint16_t port)
        {
            if (!localaddr) {
                throw NullPointer("localaddr");
            }

            mListener = MakePointer<TcpListener>(localaddr, port);
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
                auto client = mListener->AcceptTcpClient();
                Vector<uint8_t> buffer(client->Available());
                HttpContext context;

                client->GetStream()->Read(buffer, 0, buffer.size());
                context.Response = MakePointer<HttpListenerResponse>(client);
                context.Request = MakePointer<HttpListenerRequest>(buffer, client->Client()->LocalEndPoint(), client->Client()->RemoteEndPoint());
            }

            return HttpContext();
        }

        Task<HttpContext> HttpListener::GetContextAsync()
        {
            return Task<HttpContext>([this]() {
                return this->GetContext();
            });
        }
    }
}
