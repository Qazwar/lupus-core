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
#include "HttpResponse.h"
#include "Encoding.h"
#include "Version.h"
#include "Uri.h"
#include "IPAddress.h"
#include "IPEndPoint.h"
#include "Stream.h"
#include "NetUtility.h"
#include "TcpClient.h"
#include "Socket.h"
#include "Integer.h"
#include "MemoryStream.h"

using namespace std;
using namespace Lupus::Net::Sockets;

namespace Lupus {
    namespace Net {
        // TODO: Implement getter and setters.

        HttpResponse::HttpResponse(shared_ptr<TcpClient> client) :
            mClient(client)
        {
            if (!client) {
                throw null_pointer("client");
            }
        }

        void HttpResponse::Abort()
        {
            mClient->Client()->LingerState({ true, 0 });
            mClient->Close();
        }

        void HttpResponse::AddHeader(String name, String value)
        {
            mHeaders[name] = value;
        }

        void HttpResponse::AppendCookie(shared_ptr<Cookie> cookie)
        {
            // TODO: Implement Cookie.
        }

        void HttpResponse::AppendHeader(String name, String value)
        {
            auto it = mHeaders.find(name);

            if (it == end(mHeaders)) {
                mHeaders[name] = value;
            } else {
                mHeaders[name] += "," + value;
            }
        }

        void HttpResponse::Close()
        {
            // TODO: Send data to client and release resources.
        }

        void HttpResponse::Close(const std::vector<uint8_t>& responseEntity, bool willBlock)
        {
            // TODO: Send entity to client and release resources.
        }

        void HttpResponse::Redirect(String url)
        {
            // TODO: Redirect to given url.
        }

        void HttpResponse::SetCookie(shared_ptr<Cookie> cookie)
        {
            // TODO: Implement Cookie.
        }

        String HttpResponse::ToString() const
        {
            // TODO: Create response string and return it.
            return "";
        }
    }
}
