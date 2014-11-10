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
#include "HttpListenerResponse.h"
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
#include "NetworkStream.h"
#include "Integer.h"

using namespace std;
using namespace Lupus::Text;
using namespace Lupus::Net::Sockets;

namespace Lupus {
    namespace Net {
        // TODO: Response fertigstellen.

        HttpListenerResponse::HttpListenerResponse(shared_ptr<TcpClient> client) :
            mClient(client)
        {
            if (!client) {
                throw null_pointer("client");
            }

            mStream = make_shared<MemoryStream>();
        }
        
        std::shared_ptr<Text::Encoding> HttpListenerResponse::ContentEncoding() const 
        {
            return mEncoding;
        }
        
        void HttpListenerResponse::ContentEncoding(std::shared_ptr<Text::Encoding> encoding) 
        {
            mEncoding = encoding;
        }
        
        size_t HttpListenerResponse::ContentLength() const 
        {
            return mContentLength;
        }
        
        void HttpListenerResponse::ContentLength(size_t length)
        {
            mContentLength = length;
        }
        
        String HttpListenerResponse::ContentType() const 
        {
            auto it = mHeaders.find("Content-Type");

            if (it != end(mHeaders)) {
                return it->second;
            } else {
                return "";
            }
        }
        
        void HttpListenerResponse::ContentType(String type) 
        {
            mHeaders["Content-Type"] = type;
        }
        
        const NameCollection<std::shared_ptr<Cookie>>& HttpListenerResponse::Cookies() const
        {
            return mCookies;
        }
        
        void HttpListenerResponse::Cookies(const NameCollection<std::shared_ptr<Cookie>>& cookies)
        {
            mCookies = cookies;
        }
        
        const NameValueCollection& HttpListenerResponse::Headers() const 
        {
            return mHeaders;
        }
        
        void HttpListenerResponse::Headers(const NameValueCollection& headers) 
        {
            mHeaders = headers;
        }
        
        bool HttpListenerResponse::KeepAlive() const 
        {
            auto it = mHeaders.find("Connection");

            if (it != end(mHeaders)) {
                return (it->second.ToLower().Contains("keep-alive"));
            } else {
                return false;
            }
        }
        
        void HttpListenerResponse::KeepAlive(bool value) 
        {
            if (value) {
                mHeaders["Connection"] = "Keep-Alive";
            } else {
                mHeaders.erase("Connection");
            }
        }
        
        std::shared_ptr<Stream> HttpListenerResponse::OutputStream() const 
        {
            return make_shared<Lupus::OutputStream>(mStream);
        }
        
        std::shared_ptr<Version> HttpListenerResponse::ProtocolVersion() const 
        {
            return mVersion;
        }
        
        void HttpListenerResponse::ProtocolVersion(std::shared_ptr<Version> version) 
        {
            mVersion = version;
        }
        
        String HttpListenerResponse::RedirectionLocation() const 
        {
            return mRedirection;
        }
        
        void HttpListenerResponse::RedirectionLocation(String redirection) 
        {
            mRedirection = redirection;
        }
        
        int32_t HttpListenerResponse::StatusCode() const 
        {
            return mStatus;
        }
        
        void HttpListenerResponse::StatusCode(int32_t status)
        {
            mStatus = status;
        }
        
        String HttpListenerResponse::StatusDescription() const 
        {
            return mStatusDescription;
        }
        
        void HttpListenerResponse::StatusDescription(String description) 
        {
            mStatusDescription = description;
        }

        void HttpListenerResponse::Abort()
        {
            mClient->Client()->LingerState({ true, 0 });
            mClient->Close();
        }

        void HttpListenerResponse::AddHeader(String name, String value)
        {
            mHeaders[name] = value;
        }

        void HttpListenerResponse::AppendCookie(shared_ptr<Cookie> cookie)
        {
            mCookies[cookie->Name()] = cookie;
        }

        void HttpListenerResponse::AppendHeader(String name, String value)
        {
            auto it = mHeaders.find(name);

            if (it == end(mHeaders)) {
                mHeaders[name] = value;
            } else {
                mHeaders[name] += "," + value;
            }
        }

        void HttpListenerResponse::Close()
        {
            vector<uint8_t> body(mStream->Length());
            mStream->Seek(0, SeekOrigin::Begin);
            mStream->Read(body, 0, body.size());
            Close(body, true);
        }

        void HttpListenerResponse::Close(const std::vector<uint8_t>& responseEntity, bool willBlock)
        {
            auto buffer = Encoding::ASCII()->GetBytes(ToString());
            auto stream = mClient->GetStream();
            // TODO: Base64 Encoding
            buffer.insert(end(buffer), begin(responseEntity), end(responseEntity));
            stream->WriteAsync(buffer, 0, buffer.size()).SetBlocking(willBlock);
            mClient->Client()->LingerState({ false, 0 });
            mClient->Close();
        }

        void HttpListenerResponse::Redirect(String url)
        {
            if (url.IsEmpty()) {
                mHeaders.erase("Location");
            } else {
                mHeaders["Location"] = url;
            }
        }

        void HttpListenerResponse::SetCookie(shared_ptr<Cookie> cookie)
        {
            if (mCookies.find(cookie->Name()) != end(mCookies)) {
                throw invalid_argument("cookie");
            } else {
                mCookies[cookie->Name()] = cookie;
            }
        }

        String HttpListenerResponse::ToString() const
        {
            String result;
            result += "HTTP/" + (mVersion->Minor() < 0 ? (Integer::ToString(mVersion->Major()) + ".x") : mVersion->ToString());

            if (mHeaders.find("Location") == end(mHeaders)) {
                result += Integer::ToString(mStatus) + " " + (mStatusDescription.IsEmpty() ? StatusToString(mStatus) : mStatusDescription) + "\r\n";
                result += "Content-Length: " + Integer::ToString(mContentLength) + "\r\n";

                if (mEncoding) {
                    result += "Content-Encoding: " + mEncoding->Name() + "\r\n";
                }

                for_each(begin(mCookies), end(mCookies), [&result](const CookiePair& pair) {
                    result += "Set-Cookie: " + pair.second->ToString() + "\r\n";
                });

                for_each(begin(mHeaders), end(mHeaders), [&result](const NameValuePair& pair) {
                    result += pair.first + ": " + pair.second + "\r\n";
                });
            } else {
                result += "302 Found\r\n";
                result += "Location: " + mHeaders.at("Location") + "\r\n";
            }

            return (result + "\r\n");
        }
    }
}
