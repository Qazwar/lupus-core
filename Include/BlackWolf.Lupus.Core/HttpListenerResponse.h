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
            HttpListenerResponse(Pointer<Sockets::TcpClient>);
            virtual ~HttpListenerResponse() = default;

            virtual Pointer<Text::Encoding> ContentEncoding() const NOEXCEPT;
            virtual void ContentEncoding(Pointer<Text::Encoding>) NOEXCEPT;
            virtual size_t ContentLength() const NOEXCEPT;
            virtual void ContentLength(size_t) NOEXCEPT;
            virtual String ContentType() const NOEXCEPT;
            virtual void ContentType(String) NOEXCEPT;
            virtual const NameCollection<Pointer<Cookie>>& Cookies() const NOEXCEPT;
            virtual void Cookies(const NameCollection<Pointer<Cookie>>&) NOEXCEPT;
            virtual const NameValueCollection& Headers() const NOEXCEPT;
            virtual void Headers(const NameValueCollection&) NOEXCEPT;
            virtual bool KeepAlive() const NOEXCEPT;
            virtual void KeepAlive(bool) NOEXCEPT;
            virtual Pointer<Stream> OutputStream() const NOEXCEPT;
            virtual Pointer<Version> ProtocolVersion() const NOEXCEPT;
            virtual void ProtocolVersion(Pointer<Version>) NOEXCEPT;
            virtual String RedirectionLocation() const NOEXCEPT;
            virtual void RedirectionLocation(String) NOEXCEPT;
            virtual int32_t StatusCode() const NOEXCEPT;
            virtual void StatusCode(int32_t) throw(InvalidArgument);
            virtual String StatusDescription() const NOEXCEPT;
            virtual void StatusDescription(String) NOEXCEPT;

            virtual void Abort() throw(SocketError, InvalidOperation);
            virtual void AddHeader(String name, String value) NOEXCEPT;
            virtual void AppendCookie(Pointer<Cookie>) NOEXCEPT;
            virtual void AppendHeader(String name, String value) NOEXCEPT;
            virtual void Close() throw(SocketError, InvalidOperation);
            virtual void Close(const Vector<uint8_t>& responseEntity, bool willBlock) throw(SocketError, InvalidOperation);
            virtual void Redirect(String url) NOEXCEPT;
            virtual void SetCookie(Pointer<Cookie>) throw(InvalidArgument);
            virtual String ToString() const NOEXCEPT;
        protected:

            static bool ValidStatusCode(int32_t code);
            static String StatusToString(int32_t code);

        private:

            Pointer<Sockets::TcpClient> mClient;
            Pointer<Stream> mStream;
            Pointer<Uri> mUrl;
            Pointer<Version> mVersion;
            Pointer<Text::Encoding> mEncoding;
            NameCollection<Pointer<Cookie>> mCookies;
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
