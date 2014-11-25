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

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    class Version;

    namespace Net {
        class LUPUSCORE_API Cookie : NonCopyable
        {
        public:
            Cookie() = default;
            Cookie(String name, String value);
            Cookie(String name, String value, String path);
            Cookie(String name, String value, String path, String domain);
            virtual ~Cookie() = default;

            virtual String Name() const NOEXCEPT;
            virtual void Name(String) NOEXCEPT;
            virtual String Value() const NOEXCEPT;
            virtual void Value(String) NOEXCEPT;
            virtual String Path() const NOEXCEPT;
            virtual void Path(String) NOEXCEPT;
            virtual String Domain() const NOEXCEPT;
            virtual void Domain(String) NOEXCEPT;
            virtual bool Expired() const NOEXCEPT;
            virtual void Expired(bool) NOEXCEPT;
            virtual bool HttpOnly() const NOEXCEPT;
            virtual void HttpOnly(bool) NOEXCEPT;
            virtual bool Secure() const NOEXCEPT;
            virtual void Secure(bool) NOEXCEPT;
            virtual TimePoint Expires() const NOEXCEPT;
            virtual void Expires(const TimePoint&) NOEXCEPT;

            virtual String ToString() const NOEXCEPT;

        private:

            String mName = "";
            String mValue = "";
            String mPath = "";
            String mDomain = "";
            bool mExpired = false;
            bool mHttpOnly = false;
            bool mSecure = false;
            TimePoint mExpires = TimePoint::min();
        };

        typedef NameCollection<Pointer<Cookie>> CookieCollection;
        typedef NamePair<Pointer<Cookie>> CookiePair;
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
