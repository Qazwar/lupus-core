#pragma once

#include <cwchar>
#include <string>
#include <memory>
#include <cstdint>
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

    LUPUSCORE_API class String RandomString(unsigned length);

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
}
