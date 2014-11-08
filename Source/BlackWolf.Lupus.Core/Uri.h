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
#include <vector>
#include <memory>
#include <utility>
#include <boost/noncopyable.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    class LUPUSCORE_API Uri : boost::noncopyable
    {
    public:

        Uri(const String& uriString) throw(std::runtime_error, std::bad_alloc, format_error);
        Uri(std::shared_ptr<Uri> baseUri, const String& uriString) throw(std::runtime_error, std::bad_alloc, format_error);
        Uri(std::shared_ptr<Uri> baseUri, std::shared_ptr<Uri> relativeUri) throw(std::runtime_error, std::bad_alloc, format_error);

        const String& Scheme() const NOEXCEPT;
        const String& UserInfo() const NOEXCEPT;
        const String& HostText() const NOEXCEPT;
        const String& HostData() const NOEXCEPT;
        const String& PortText() const NOEXCEPT;
        const std::vector<String>& PathHead() const NOEXCEPT;
        const std::vector<String>& PathTail() const NOEXCEPT;
        const String& Query() const NOEXCEPT;
        const String& Fragment() const NOEXCEPT;
        const String& OriginalString() const NOEXCEPT;
        bool IsAbsolutePath() const NOEXCEPT;

        String FullPath() const NOEXCEPT;
        String ToString() const NOEXCEPT;

        static String Encode(const String&);
        static String Decode(const String&);
        static bool CheckSchemeName(const String&);

    private:

        String mScheme;
        String mUserInfo;
        String mHostText;
        String mHostData;
        String mPortText;
        std::vector<String> mPathHead;
        std::vector<String> mPathTail;
        String mQuery;
        String mFragment;
        String mOriginalString;
        bool mIsAbosultePath;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
