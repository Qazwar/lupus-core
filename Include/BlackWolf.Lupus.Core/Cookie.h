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
#include <boost/noncopyable.hpp>

namespace Lupus {
    class Version;

    namespace Net {
        class LUPUSCORE_API Cookie : boost::noncopyable
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

        typedef NameCollection<std::shared_ptr<Cookie>> CookieCollection;
        typedef NamePair<std::shared_ptr<Cookie>> CookiePair;
    }
}
