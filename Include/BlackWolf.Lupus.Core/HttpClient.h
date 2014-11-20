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

#include "Utility.h"

namespace Lupus {
    class Uri;

    namespace Net {
        namespace Sockets {
            class TcpClient;
        }

        // TODO: HttpClient fertigstellen.
        class LUPUSCORE_API HttpClient : NonCopyable
        {
        public:

            HttpClient() = default;
            virtual ~HttpClient() = default;

            virtual Pointer<Uri> BaseAddress() const NOEXCEPT;
            virtual void BaseAddress(Pointer<Uri>) NOEXCEPT;
            virtual const NameValueCollection& DefaultRequestHeaders() const NOEXCEPT;
            virtual void DefaultRequestHeaders(const NameValueCollection&) NOEXCEPT;
            virtual size_t MaxResponseContentBufferSize() const NOEXCEPT;
            virtual void MaxResponseContentBufferSize(size_t) NOEXCEPT;

            template <typename Rep, typename Period>
            std::chrono::duration<Rep, Period> Timeout() const throw(SocketError, InvalidOperation)
            {
                return std::chrono::duration_cast<std::chrono::duration<Rep, Period>>(std::chrono::milliseconds(mClient->SendTimeout()));
            }

            template <typename Rep, typename Period>
            void Timeout(const std::chrono::duration<Rep, Period>& value) throw(SocketError, InvalidOperation)
            {
                mClient->SendTimeout(static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(value).count()));
            }

        private:

            Pointer<Sockets::TcpClient> mClient;
        };
    }
}
