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


using namespace Lupus::Text;
using namespace Lupus::Net::Sockets;

namespace Lupus {
    namespace Net {
        HttpListenerResponse::HttpListenerResponse(Pointer<TcpClient> client) :
            mClient(client)
        {
            if (!client) {
                throw NullPointer("client");
            }

            mStream = MakePointer<MemoryStream>();
        }
        
        Pointer<Text::Encoding> HttpListenerResponse::ContentEncoding() const 
        {
            return mEncoding;
        }
        
        void HttpListenerResponse::ContentEncoding(Pointer<Text::Encoding> encoding) 
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
        
        const NameCollection<Pointer<Cookie>>& HttpListenerResponse::Cookies() const
        {
            return mCookies;
        }
        
        void HttpListenerResponse::Cookies(const NameCollection<Pointer<Cookie>>& cookies)
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
        
        Pointer<Stream> HttpListenerResponse::OutputStream() const 
        {
            return MakePointer<Lupus::OutputStream>(mStream);
        }
        
        Pointer<Version> HttpListenerResponse::ProtocolVersion() const 
        {
            return mVersion;
        }
        
        void HttpListenerResponse::ProtocolVersion(Pointer<Version> version) 
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
            if (!ValidStatusCode(status)) {
                throw InvalidArgument("status");
            }

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

        void HttpListenerResponse::AppendCookie(Pointer<Cookie> cookie)
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
            Vector<uint8_t> body((size_t)mStream->Length());
            mStream->Seek(0, SeekOrigin::Begin);
            mStream->Read(body, 0, body.size());
            Close(body, true);
        }

        void HttpListenerResponse::Close(const Vector<uint8_t>& responseEntity, bool willBlock)
        {
            auto buffer = Encoding::ASCII()->GetBytes(ToString());
            auto stream = mClient->GetStream();
            // TODO: Base64 Encoding for responseEntity
            buffer.insert(end(buffer), begin(responseEntity), end(responseEntity));
            stream->WriteAsync(buffer, 0, buffer.size()).SetBlocking(willBlock);
        }

        void HttpListenerResponse::Redirect(String url)
        {
            if (url.IsEmpty()) {
                mHeaders.erase("Location");
            } else {
                mHeaders["Location"] = url;
            }
        }

        void HttpListenerResponse::SetCookie(Pointer<Cookie> cookie)
        {
            if (mCookies.find(cookie->Name()) != end(mCookies)) {
                throw InvalidArgument("cookie");
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
                result += "302 " + StatusToString(302) + "\r\n";
                result += "Location: " + mHeaders.at("Location") + "\r\n";
            }

            return (result + "\r\n");
        }

        bool HttpListenerResponse::ValidStatusCode(int32_t value)
        {
            return (value >= 100 && value <= 999);
        }

        String HttpListenerResponse::StatusToString(int32_t value)
        {
            static const Collection<int32_t, String> sState = {
                // 100
                { 100, "Continue" },
                { 101, "Switching Protocols" },
                { 102, "Processing" },

                // 200
                { 200, "OK" },
                { 201, "Created" },
                { 202, "Accepted" },
                { 203, "Non-Authorative Information" },
                { 204, "No Content" },
                { 205, "Reset Content" },
                { 206, "Partial Content" },
                { 207, "Multi-Status" },
                { 208, "Already Reported" },
                { 226, "IM Used" },

                // 300
                { 300, "Multiple Choices" },
                { 301, "Moved Permanently" },
                { 302, "Found" },
                { 303, "See Other" },
                { 304, "Not Modified" },
                { 305, "Use Proxy" },
                { 306, "Switch Proxy" },
                { 307, "Temporary Redirect" },
                { 308, "Permanent Redirect" },

                // 400
                { 400, "Bad Request" },
                { 401, "Unauthorized" },
                { 402, "Payment Required" },
                { 403, "Forbidden" },
                { 404, "Not Found" },
                { 405, "Method Not Allowed" },
                { 406, "Not Acceptable" },
                { 407, "Proxy Authentication Required" },
                { 408, "Request Timeout" },
                { 409, "Conflict" },
                { 410, "Gone" },
                { 411, "Length Required" },
                { 412, "Precondition Failed" },
                { 413, "Request Entity Too Large" },
                { 414, "Request-URI Too Long" },
                { 415, "Unsupported Media Type" },
                { 416, "Requested Range Not Satisfiable" },
                { 417, "Expectation Failed" },
                { 418, "I'm a teapot" },
                { 419, "Authentication Timeout" },
                { 422, "Unprocessable Entity" },
                { 423, "Locked" },
                { 424, "Failed Dependency" },
                { 426, "Upgrade Required" },
                { 428, "Precondition Required" },
                { 429, "Too Many Requests" },
                { 431, "Request Header Fields Too Large" },
                { 451, "Unavailable For Legal Reasons" },

                // 500
                { 500, "Internal Server Error" },
                { 501, "Not Implemented" },
                { 502, "Bad Gateway" },
                { 503, "Service Unavailable" },
                { 504, "Gateway Timeout" },
                { 505, "HTTP Version Not Supported" },
                { 506, "Variant Also Negotiates" },
                { 507, "Insufficient Storage" },
                { 508, "Loop Detected" },
                { 510, "Not Extended" },
                { 511, "Network Authentication Required" }
            };

            auto it = sState.find(value);

            if (it != end(sState)) {
                return it->second;
            } else {
                return "Unknown";
            }
        }
    }
}
