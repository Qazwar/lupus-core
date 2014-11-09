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

#include <cstdlib>
#include <cstdint>
#include <cwchar>
#include <string>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <exception>

#ifdef NOEXCEPT
#undef NOEXCEPT
#endif

#ifdef _MSC_VER
#pragma warning(disable: 4290)
#define NOEXCEPT throw()

#ifdef LUPUSCORE_EXPORT
#define LUPUSCORE_API __declspec(dllexport)
#else
#define LUPUSCORE_API __declspec(dllimport)
#endif

#else
#define NOEXCEPT noexcept

#ifdef LUPUSCORE_EXPORT

#ifdef __CYGWIN__
#define LUPUSCORE_API __attribute__ ((dllexport))
#else
#define LUPUSCORE_API __attribute__ ((visibility ("default")))
#endif

#else

#ifdef __CYGWIN__
#define LUPUSCORE_API __attribute__ ((dllimport))
#else
#define LUPUSCORE_API __attribute__ ((visibility ("default")))
#endif

#endif
#endif

#define LupusDefineError(cls) \
    class cls : public virtual std::exception \
    { \
        std::string mMessage; \
    public: \
        inline cls(const std::string& message = "") : mMessage(message) { } \
        virtual ~cls() = default; \
        cls& operator=(const cls&) = default; \
        virtual inline const char* what() const override { return mMessage.c_str(); } \
    }

#define LupusFlagEnumeration(type) \
    inline type operator|(type lhs, type rhs) \
    { \
        return static_cast<type>(static_cast<int>(lhs) | static_cast<int>(rhs)); \
    } \
    inline type operator&(type lhs, type rhs) \
    { \
        return static_cast<type>(static_cast<int>(lhs) & static_cast<int>(rhs)); \
    } \
    inline type& operator|=(type& lhs, type rhs) \
    { \
        lhs = static_cast<type>(static_cast<int>(lhs) | static_cast<int>(rhs)); \
        return lhs; \
    } \
    inline type& operator&=(type& lhs, type rhs) \
    { \
        lhs = static_cast<type>(static_cast<int>(lhs) & static_cast<int>(rhs)); \
        return lhs; \
    }

#define LupusCreateFlag(name, n) name = (0x00000001 << n)
#define LupusCreateNoFlag(name) name = 0

namespace Lupus {
    LupusDefineError(null_pointer);
    LupusDefineError(sql_error);
    LupusDefineError(socket_error);
    LupusDefineError(http_error);
    LupusDefineError(io_error);
    LupusDefineError(not_supported);
    LupusDefineError(unauthorized_access);
    LupusDefineError(authentication_error);
    LupusDefineError(format_error);

    LUPUSCORE_API class String RandomString(uint32_t length);

    template <typename Dest, typename Src>
    Dest force_cast(const Src& src)
    {
        union types {
            Src s;
            Dest d;
        } t;

        t.s = src;
        return t.d;
    }

    template <typename FlagType>
    bool HasFlag(FlagType flag, FlagType flags)
    {
        return ((flags & flag) == flag);
    }

    LUPUSCORE_API std::shared_ptr<class Version> GetVersion();

    typedef std::unordered_map<class String, class String> NameValueCollection;
    typedef std::pair<class String, class String> NameValuePair;

    template <typename Value>
    using NameCollection = std::unordered_map < class String, Value > ;
}
