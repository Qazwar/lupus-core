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

#include <cstdlib>
#include <cstdint>
#include <cwchar>
#include <string>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <exception>
#include <chrono>
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

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
    LupusDefineError(socket_error);
    LupusDefineError(http_error);
    LupusDefineError(io_error);
    LupusDefineError(not_supported);
    LupusDefineError(unauthorized_access);
    LupusDefineError(authentication_error);
    LupusDefineError(format_error);
    LupusDefineError(invalid_operation);

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

    template <typename TValue>
    using NameCollection = std::unordered_map < class String, TValue > ;
    template <typename TValue>
    using NamePair = std::pair < class String, TValue > ;

    template <typename TKey, typename TValue>
    using Collection = std::unordered_map < TKey, TValue > ;
    template <typename TKey, typename TValue>
    using Pair = std::pair < TKey, TValue > ;

    typedef boost::any Any;
    typedef boost::noncopyable NonCopyable;

    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::time_point<Clock> TimePoint;
    typedef std::chrono::nanoseconds Nanoseconds;
    typedef std::chrono::microseconds Microseconds;
    typedef std::chrono::milliseconds Milliseconds;
    typedef std::chrono::seconds Seconds;
    typedef std::chrono::minutes Minutes;
    typedef std::chrono::hours Hours;
}
