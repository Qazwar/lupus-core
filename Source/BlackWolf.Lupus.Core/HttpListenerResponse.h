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
#pragma once

#include "String.h"
#include "Task.h"

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

        class LUPUSCORE_API HttpListenerResponse : public NonCopyable
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
            virtual void StatusCode(int32_t) throw(std::invalid_argument);
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
