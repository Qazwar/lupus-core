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

#include "String.h"
#include "Task.h"
#include <vector>
#include <memory>
#include <cstdint>
#include <unordered_map>
#include <boost/noncopyable.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    class Stream;
    class InputStream;
    class Uri;
    class Version;

    namespace Security {
        namespace Cryptography {
            namespace X509Certificates {
                class X509Certificate;
            }
        }
    }

    namespace Text {
        class Encoding;
    }

    namespace Net {
        namespace Sockets {
            class IPEndPoint;
        }

        class LUPUSCORE_API HttpListenerRequest : public boost::noncopyable
        {
        public:

            HttpListenerRequest() = delete;
            HttpListenerRequest(
                const std::vector<uint8_t>& buffer,
                std::shared_ptr<Sockets::IPEndPoint> localEP,
                std::shared_ptr<Sockets::IPEndPoint> remoteEP,
                bool authenticated = false,
                bool secure = false);
            virtual ~HttpListenerRequest() = default;

            const std::vector<String>& AcceptTypes() const NOEXCEPT;
            std::shared_ptr<Text::Encoding> ContentEncoding() const NOEXCEPT;
            int64_t ContentLength() const NOEXCEPT;
            String ContentType() const NOEXCEPT;
            const std::unordered_map<String, String>& Cookies() const NOEXCEPT;
            bool HasEntityBody() const NOEXCEPT;
            const std::unordered_map<String, String>& Headers() const NOEXCEPT;
            String HttpMethod() const NOEXCEPT;
            std::shared_ptr<Stream> InputStream() const NOEXCEPT;
            bool IsAuthenticated() const NOEXCEPT;
            bool IsLocal() const NOEXCEPT;
            bool IsSecureConnection() const NOEXCEPT;
            bool KeepAlive() const NOEXCEPT;
            String LocalAddress() const NOEXCEPT;
            std::shared_ptr<Sockets::IPEndPoint> LocalEndPoint() const NOEXCEPT;
            std::shared_ptr<Version> ProtocolVersion() const NOEXCEPT;
            const std::unordered_map<String, String>& QueryString() const NOEXCEPT;
            String RawHeader() const NOEXCEPT;
            String RemoteAddress() const NOEXCEPT;
            std::shared_ptr<Sockets::IPEndPoint> RemoteEndPoint() const NOEXCEPT;
            std::shared_ptr<Uri> Url() const NOEXCEPT;
            String UserAgent() const NOEXCEPT;
            const std::vector<String>& UserLanguages() const NOEXCEPT;

            /**
             * \warning Not implemented.
             */
            Task<std::shared_ptr<Lupus::Security::Cryptography::X509Certificates::X509Certificate>> GetClientCertificateAsync() const NOEXCEPT;

            /**
             * \warning Not implemented.
             */
            std::shared_ptr<Lupus::Security::Cryptography::X509Certificates::X509Certificate> GetClientCertificate() const NOEXCEPT;

        private:

            std::shared_ptr<Lupus::Stream> mStream;
            std::shared_ptr<Sockets::IPEndPoint> mLocalEP;
            std::shared_ptr<Sockets::IPEndPoint> mRemoteEP;
            std::shared_ptr<Uri> mUrl;
            std::shared_ptr<Version> mVersion;
            std::shared_ptr<Text::Encoding> mEncoding;
            std::unordered_map<String, String> mCookies;
            std::unordered_map<String, String> mHeaders;
            std::unordered_map<String, String> mQuery;
            std::vector<String> mAcceptedTypes;
            std::vector<String> mLanguages;
            String mContentType;
            String mMethod;
            String mUserAgent;
            String mRawHeader;
            bool mAuthenticated = false;
            bool mSecure = false;
        };
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
