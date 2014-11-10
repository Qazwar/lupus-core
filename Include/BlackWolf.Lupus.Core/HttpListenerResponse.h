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
#include <boost/noncopyable.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    class Stream;
    class Uri;
    class Version;

    namespace Text {
        class Encoding;
    }

    namespace Net {
        namespace Sockets {
            class TcpClient;
        }

        class Cookie;

        class LUPUSCORE_API HttpListenerResponse : public boost::noncopyable
        {
        public:
            HttpListenerResponse() = delete;
            HttpListenerResponse(std::shared_ptr<Sockets::TcpClient>);
            virtual ~HttpListenerResponse() = default;

            virtual std::shared_ptr<Text::Encoding> ContentEncoding() const NOEXCEPT;
            virtual void ContentEncoding(std::shared_ptr<Text::Encoding>) NOEXCEPT;
            virtual size_t ContentLength() const NOEXCEPT;
            virtual void ContentLength(size_t) NOEXCEPT;
            virtual String ContentType() const NOEXCEPT;
            virtual void ContentType(String) NOEXCEPT;
            virtual const NameCollection<std::shared_ptr<Cookie>>& Cookies() const NOEXCEPT;
            virtual void Cookies(const NameCollection<std::shared_ptr<Cookie>>&) NOEXCEPT;
            virtual const NameValueCollection& Headers() const NOEXCEPT;
            virtual void Headers(const NameValueCollection&) NOEXCEPT;
            virtual bool KeepAlive() const NOEXCEPT;
            virtual void KeepAlive(bool) NOEXCEPT;
            virtual std::shared_ptr<Stream> OutputStream() const NOEXCEPT;
            virtual std::shared_ptr<Version> ProtocolVersion() const NOEXCEPT;
            virtual void ProtocolVersion(std::shared_ptr<Version>) NOEXCEPT;
            virtual String RedirectionLocation() const NOEXCEPT;
            virtual void RedirectionLocation(String) NOEXCEPT;
            virtual int32_t StatusCode() const NOEXCEPT;
            virtual void StatusCode(int32_t) NOEXCEPT;
            virtual String StatusDescription() const NOEXCEPT;
            virtual void StatusDescription(String) NOEXCEPT;

            virtual void Abort() throw(socket_error, invalid_operation);
            virtual void AddHeader(String name, String value) NOEXCEPT;
            virtual void AppendCookie(std::shared_ptr<Cookie>) NOEXCEPT;
            virtual void AppendHeader(String name, String value) NOEXCEPT;
            virtual void Close() throw(socket_error, invalid_operation);
            virtual void Close(const std::vector<uint8_t>& responseEntity, bool willBlock) throw(socket_error, invalid_operation);
            virtual void Redirect(String url) NOEXCEPT;
            virtual void SetCookie(std::shared_ptr<Cookie>) throw(std::invalid_argument);
            virtual String ToString() const NOEXCEPT;
        protected:

            static bool ValidStatusCode(int32_t code);
            static String StatusToString(int32_t code);

        private:

            std::shared_ptr<Sockets::TcpClient> mClient;
            std::shared_ptr<Stream> mStream;
            std::shared_ptr<Uri> mUrl;
            std::shared_ptr<Version> mVersion;
            std::shared_ptr<Text::Encoding> mEncoding;
            NameCollection<std::shared_ptr<Cookie>> mCookies;
            NameValueCollection mHeaders;
            String mRedirection;
            String mStatusDescription;
            size_t mContentLength;
            int32_t mStatus;
        };
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
