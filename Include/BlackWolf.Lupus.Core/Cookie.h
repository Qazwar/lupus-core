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
    namespace Net {
        // TODO: Fertig implementieren.

        class LUPUSCORE_API Cookie : boost::noncopyable
        {
        public:
            Cookie() = default;
            Cookie(String name, String value);
            Cookie(String name, String value, String path);
            Cookie(String name, String value, String path, String domain);
            virtual ~Cookie() = default;
        };

        typedef NameCollection<std::shared_ptr<Cookie>> CookieCollection;
        typedef NamePair<std::shared_ptr<Cookie>> NameCookiePair;
    }
}
