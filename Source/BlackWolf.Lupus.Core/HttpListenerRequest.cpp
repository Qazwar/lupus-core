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
#include "HttpListenerRequest.h"
#include "Encoding.h"
#include "Version.h"
#include "Uri.h"
#include "IPAddress.h"
#include "IPEndPoint.h"
#include "Stream.h"
#include "NetUtility.h"
#include "Integer.h"
#include "MemoryStream.h"
#include "X509Certificate.h"
#include "Cookie.h"


using namespace Lupus::Text;
using namespace Lupus::Net::Sockets;
using namespace Lupus::Security::Cryptography::X509Certificates;

namespace Lupus {
    namespace Net {
        HttpListenerRequest::HttpListenerRequest(const Vector<U8>& buffer, Pointer<IPEndPoint> local, Pointer<IPEndPoint> remote, bool auth, bool sec) :
            mLocalEP(local), mRemoteEP(remote), mAuthenticated(auth), mSecure(sec)
        {
            NameValueCollection::const_iterator citum;

            for (auto it = Begin(buffer); it != End(buffer); it++) {
                char ch = static_cast<char>(*it);
                
                if (ch == '\r' && static_cast<char>(*(it + 1)) == '\n' && static_cast<char>(*(it + 2)) == '\r' && static_cast<char>(*(it + 3)) == '\n') {
                    it += 4;
                    mRawHeader = Encoding::ASCII()->GetString(Vector<U8>(Begin(buffer), it));
                    mStream = MakePointer<MemoryStream>(buffer, distance(Begin(buffer), it), distance(it, End(buffer)), false, true);
                    break;
                }
            }

            Vector<String> lines = mRawHeader.Split("\r\n", StringSplitOption::RemoveEmptyEntries);
            Vector<String> fields(Begin(lines) + 1, End(lines));
            String version = lines[0].Substring(lines[0].LastIndexOf("/") + 1);
            
            mMethod = lines[0].Substring(0, lines[0].IndexOf(" "));
            mVersion = Version::Parse(version);

            for (String str : fields) {
                Vector<String> field = str.Split(": ");
                mHeaders[field[0]] = field[1];
            }

            int index = lines[0].IndexOf(" ") + 1;
            mUrl = MakePointer<Uri>((mSecure ? "https://" : "http://") + mHeaders["Host"] + lines[0].Substring(index, lines[0].LastIndexOf(" ") - index));
            String query = mUrl->Query();
            String cookie = (citum = mHeaders.find("Cookie")) != End(mHeaders) ? citum->second : "";
            String language = (citum = mHeaders.find("Accept-Language")) != End(mHeaders) ? citum->second : "";
            String charset = (citum = mHeaders.find("Accept-Charset")) != End(mHeaders) ? citum->second : "";
            String accepttypes = (citum = mHeaders.find("Accept")) != End(mHeaders) ? citum->second : "";

            mContentType = (citum = mHeaders.find("Content-Type")) != End(mHeaders) ? citum->second : "";
            mUserAgent = (citum = mHeaders.find("User-Agent")) != End(mHeaders) ? citum->second : "";

            mAcceptedTypes = accepttypes.IsEmpty() ? Vector<String>() : accepttypes.Split(";")[0].Split(",", StringSplitOption::RemoveEmptyEntries);
            mLanguages = language.IsEmpty() ? Vector<String>() : language.Split(";")[0].Split(",", StringSplitOption::RemoveEmptyEntries);
            auto queries = query.IsEmpty() ? Vector<String>() : query.Split("&", StringSplitOption::RemoveEmptyEntries);

            for (auto str : queries) {
                auto nameValuePair = str.Split("=");
                mQuery[nameValuePair[0]] = nameValuePair[1];
            }

            auto cookies = cookie.Split(";", StringSplitOption::RemoveEmptyEntries);

            for (auto str : cookies) {
                auto nameValuePair = str.Split("=");
                mCookies[nameValuePair[0]] = MakePointer<Cookie>(nameValuePair[0], nameValuePair[1]);
            }

            if (charset.IsEmpty()) {
                mEncoding = Encoding::UTF8();
            } else {
                auto encodings = charset.Split(";", StringSplitOption::RemoveEmptyEntries)[0].Split(",", StringSplitOption::RemoveEmptyEntries);

                for (auto enc : encodings) {
                    if (enc.Compare("utf-8", StringCaseSensitivity::CaseInsensitive) == 0) {
                        mEncoding = Encoding::UTF8();
                        break;
                    } else if (!mEncoding) {
                        mEncoding = Encoding::GetEncoding(enc);
                    }
                }

                if (!mEncoding) {
                    mEncoding = Encoding::UTF8();
                }
            }
        }

        const Vector<String>& HttpListenerRequest::AcceptTypes() const
        {
            return mAcceptedTypes;
        }
        
        Pointer<Text::Encoding> HttpListenerRequest::ContentEncoding() const
        {
            return mEncoding;
        }
        
        S64 HttpListenerRequest::ContentLength() const
        {
            return mStream->Length();
        }
        
        String HttpListenerRequest::ContentType() const
        {
            return mContentType;
        }
        
        const CookieCollection& HttpListenerRequest::Cookies() const
        {
            return mCookies;
        }
        
        bool HttpListenerRequest::HasEntityBody() const
        {
            return mStream->Length() != 0;
        }
        
        const NameValueCollection& HttpListenerRequest::Headers() const
        {
            return mHeaders;
        }
        
        String HttpListenerRequest::HttpMethod() const
        {
            return mMethod;
        }
        
        Pointer<Stream> HttpListenerRequest::InputStream() const
        {
            return mStream;
        }
        
        bool HttpListenerRequest::IsAuthenticated() const
        {
            return mAuthenticated;
        }
        
        bool HttpListenerRequest::IsLocal() const
        {
            return IPAddress::IsLoopback(mRemoteEP->Address());
        }
        
        bool HttpListenerRequest::IsSecureConnection() const
        {
            return mSecure;
        }
        
        bool HttpListenerRequest::KeepAlive() const
        {
            if (mHeaders.find("Connection") == End(mHeaders)) {
                return false;
            } else {
                return mHeaders.at("Connection").Contains("keep-alive");
            }
        }

        String HttpListenerRequest::LocalAddress() const
        {
            return mLocalEP->Address()->ToString() + (mLocalEP->Port() != 80 && mLocalEP->Port() != 443 ? ":" + Integer::ToString(mLocalEP->Port()) : "");
        }
        
        Pointer<Sockets::IPEndPoint> HttpListenerRequest::LocalEndPoint() const
        {
            return mLocalEP;
        }
        
        Pointer<Version> HttpListenerRequest::ProtocolVersion() const
        {
            return mVersion;
        }
        
        const NameValueCollection& HttpListenerRequest::QueryString() const
        {
            return mQuery;
        }
        
        String HttpListenerRequest::RawHeader() const
        {
            return mRawHeader;
        }

        String HttpListenerRequest::RemoteAddress() const
        {
            return mRemoteEP->Address()->ToString() + (mRemoteEP->Port() != 80 && mRemoteEP->Port() != 443 ? ":" + Integer::ToString(mRemoteEP->Port()) : "");
        }
        
        Pointer<Sockets::IPEndPoint> HttpListenerRequest::RemoteEndPoint() const
        {
            return mRemoteEP;
        }
        
        Pointer<Uri> HttpListenerRequest::Url() const
        {
            return mUrl;
        }
        
        String HttpListenerRequest::UserAgent() const
        {
            return mUserAgent;
        }
        
        const Vector<String>& HttpListenerRequest::UserLanguages() const
        {
            return mLanguages;
        }

        String HttpListenerRequest::ToString() const
        {
            return mRawHeader;
        }

        Task<Pointer<X509Certificate>> HttpListenerRequest::GetClientCertificateAsync() const
        {
            return Task<Pointer<X509Certificate>>([this]() {
                return this->GetClientCertificate();
            });
        }

        Pointer<X509Certificate> HttpListenerRequest::GetClientCertificate() const
        {
            return nullptr;
        }
    }
}
