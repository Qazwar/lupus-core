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
#include "Cookie.h"

using namespace std;
using namespace Lupus::Net::Sockets;

namespace Lupus {
    namespace Net {
        // TODO: Response fertigstellen.

        HttpResponse::HttpResponse(shared_ptr<TcpClient> client) :
            mClient(client)
        {
            if (!client) {
                throw null_pointer("client");
            }

            mStream = make_shared<Lupus::OutputStream>(make_shared<MemoryStream>());
        }
        
        std::shared_ptr<Text::Encoding> HttpResponse::ContentEncoding() const 
        {
            return mEncoding;
        }
        
        void HttpResponse::ContentEncoding(std::shared_ptr<Text::Encoding> encoding) 
        {
            mEncoding = encoding;
        }
        
        size_t HttpResponse::ContentLength() const 
        {
            return mContentLength;
        }
        
        void HttpResponse::ContentLength(size_t length)
        {
            mContentLength = length;
        }
        
        String HttpResponse::ContentType() const 
        {
            return mContentType;
        }
        
        void HttpResponse::ContentType(String type) 
        {
            mContentType = type;
        }
        
        const NameCollection<std::shared_ptr<Cookie>>& HttpResponse::Cookies() const
        {
            return mCookies;
        }
        
        void HttpResponse::Cookies(const NameCollection<std::shared_ptr<Cookie>>& cookies)
        {
            mCookies = cookies;
        }
        
        const NameValueCollection& HttpResponse::Headers() const 
        {
            return mHeaders;
        }
        
        void HttpResponse::Headers(const NameValueCollection& headers) 
        {
            mHeaders = headers;
        }
        
        bool HttpResponse::KeepAlive() const 
        {
            return mKeepAlive;
        }
        
        void HttpResponse::KeepAlive(bool b) 
        {
            mKeepAlive = b;
        }
        
        std::shared_ptr<Stream> HttpResponse::OutputStream() const 
        {
            return mStream;
        }
        
        std::shared_ptr<Version> HttpResponse::ProtocolVersion() const 
        {
            return mVersion;
        }
        
        void HttpResponse::ProtocolVersion(std::shared_ptr<Version> version) 
        {
            mVersion = version;
        }
        
        String HttpResponse::RedirectionLocation() const 
        {
            return mRedirection;
        }
        
        void HttpResponse::RedirectionLocation(String redirection) 
        {
            mRedirection = redirection;
        }
        
        uint16_t HttpResponse::StatusCode() const 
        {
            return mStatus;
        }
        
        void HttpResponse::StatusCode(uint16_t status) 
        {
            mStatus = status;
        }
        
        String HttpResponse::StatusDescription() const 
        {
            return mStatusDescription;
        }
        
        void HttpResponse::StatusDescription(String description) 
        {
            mStatusDescription = description;
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
