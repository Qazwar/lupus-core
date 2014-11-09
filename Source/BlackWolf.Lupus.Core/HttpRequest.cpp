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
#include "HttpRequest.h"
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

using namespace std;
using namespace Lupus::Text;
using namespace Lupus::Net::Sockets;
using namespace Lupus::Security::Cryptography::X509Certificates;

namespace Lupus {
    namespace Net {
        HttpRequest::HttpRequest(const vector<uint8_t>& buffer, shared_ptr<IPEndPoint> local, shared_ptr<IPEndPoint> remote, bool auth, bool sec) :
            mLocalEP(local), mRemoteEP(remote), mAuthenticated(auth), mSecure(sec)
        {
            unordered_map<String, String>::const_iterator citum;

            for (auto it = begin(buffer); it != end(buffer); it++) {
                char ch = static_cast<char>(*it);
                
                if (ch == '\r' && static_cast<char>(*(it + 1)) == '\n' && static_cast<char>(*(it + 2)) == '\r' && static_cast<char>(*(it + 3)) == '\n') {
                    it += 4;
                    mRawHeader = Encoding::ASCII()->GetString(vector<uint8_t>(begin(buffer), it));
                    mStream = make_shared<MemoryStream>(buffer, distance(begin(buffer), it), distance(it, end(buffer)), false, true);
                    break;
                }
            }

            vector<String> lines = mRawHeader.Split("\r\n", StringSplitOption::RemoveEmptyEntries);
            vector<String> fields(begin(lines) + 1, end(lines));
            String version = lines[0].Substring(lines[0].LastIndexOf("/") + 1);
            
            mMethod = lines[0].Substring(0, lines[0].IndexOf(" "));
            mVersion = Version::Parse(version);

            for (String str : fields) {
                vector<String> field = str.Split(": ");
                mHeaders[field[0]] = field[1];
            }

            int index = lines[0].IndexOf(" ") + 1;
            mUrl = make_shared<Uri>((mSecure ? "https://" : "http://") + mHeaders["Host"] + lines[0].Substring(index, lines[0].LastIndexOf(" ") - index));
            String query = mUrl->Query();
            String cookie = (citum = mHeaders.find("Cookie")) != end(mHeaders) ? citum->second : "";
            String language = (citum = mHeaders.find("Accept-Language")) != end(mHeaders) ? citum->second : "";
            String charset = (citum = mHeaders.find("Accept-Charset")) != end(mHeaders) ? citum->second : "";
            String accepttypes = (citum = mHeaders.find("Accept")) != end(mHeaders) ? citum->second : "";

            mContentType = (citum = mHeaders.find("Content-Type")) != end(mHeaders) ? citum->second : "";
            mUserAgent = (citum = mHeaders.find("User-Agent")) != end(mHeaders) ? citum->second : "";

            mAcceptedTypes = accepttypes.IsEmpty() ? vector<String>() : accepttypes.Split(";")[0].Split(",", StringSplitOption::RemoveEmptyEntries);
            mLanguages = language.IsEmpty() ? vector<String>() : language.Split(";")[0].Split(",", StringSplitOption::RemoveEmptyEntries);
            auto queries = query.IsEmpty() ? vector<String>() : query.Split("&", StringSplitOption::RemoveEmptyEntries);

            for (auto str : queries) {
                auto nameValuePair = str.Split("=");
                mQuery[nameValuePair[0]] = nameValuePair[1];
            }

            auto cookies = cookie.Split(";", StringSplitOption::RemoveEmptyEntries);

            for (auto str : cookies) {
                auto nameValuePair = str.Split("=");
                mCookies[nameValuePair[0]] = nameValuePair[1];
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

        const vector<String>& HttpRequest::AcceptTypes() const
        {
            return mAcceptedTypes;
        }
        
        shared_ptr<Text::Encoding> HttpRequest::ContentEncoding() const
        {
            return mEncoding;
        }
        
        int64_t HttpRequest::ContentLength() const
        {
            return mStream->Length();
        }
        
        String HttpRequest::ContentType() const
        {
            return mContentType;
        }
        
        const unordered_map<String, String>& HttpRequest::Cookies() const
        {
            return mCookies;
        }
        
        bool HttpRequest::HasEntityBody() const
        {
            return mStream->Length() != 0;
        }
        
        const unordered_map<String, String>& HttpRequest::Headers() const
        {
            return mHeaders;
        }
        
        String HttpRequest::HttpMethod() const
        {
            return mMethod;
        }
        
        shared_ptr<Stream> HttpRequest::InputStream() const
        {
            return mStream;
        }
        
        bool HttpRequest::IsAuthenticated() const
        {
            return mAuthenticated;
        }
        
        bool HttpRequest::IsLocal() const
        {
            return IPAddress::IsLoopback(mRemoteEP->Address());
        }
        
        bool HttpRequest::IsSecureConnection() const
        {
            return mSecure;
        }
        
        bool HttpRequest::KeepAlive() const
        {
            if (mHeaders.find("Connection") == end(mHeaders)) {
                return false;
            } else {
                return mHeaders.at("Connection").Contains("keep-alive");
            }
        }

        String HttpRequest::LocalAddress() const
        {
            return mLocalEP->Address()->ToString() + (mLocalEP->Port() != 80 && mLocalEP->Port() != 443 ? ":" + Integer::ToString(mLocalEP->Port()) : "");
        }
        
        shared_ptr<Sockets::IPEndPoint> HttpRequest::LocalEndPoint() const
        {
            return mLocalEP;
        }
        
        shared_ptr<Version> HttpRequest::ProtocolVersion() const
        {
            return mVersion;
        }
        
        const unordered_map<String, String>& HttpRequest::QueryString() const
        {
            return mQuery;
        }
        
        String HttpRequest::RawHeader() const
        {
            return mRawHeader;
        }

        String HttpRequest::RemoteAddress() const
        {
            return mRemoteEP->Address()->ToString() + (mRemoteEP->Port() != 80 && mRemoteEP->Port() != 443 ? ":" + Integer::ToString(mRemoteEP->Port()) : "");
        }
        
        shared_ptr<Sockets::IPEndPoint> HttpRequest::RemoteEndPoint() const
        {
            return mRemoteEP;
        }
        
        shared_ptr<Uri> HttpRequest::Url() const
        {
            return mUrl;
        }
        
        String HttpRequest::UserAgent() const
        {
            return mUserAgent;
        }
        
        const vector<String>& HttpRequest::UserLanguages() const
        {
            return mLanguages;
        }

        Task<shared_ptr<X509Certificate>> HttpRequest::GetClientCertificateAsync() const
        {
            return Task<shared_ptr<X509Certificate>>([this]() {
                return this->GetClientCertificate();
            });
        }

        shared_ptr<X509Certificate> HttpRequest::GetClientCertificate() const
        {
            return nullptr;
        }
    }
}
