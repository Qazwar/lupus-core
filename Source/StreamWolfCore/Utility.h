#pragma once

#include <string>
#include <exception>

#ifdef _MSC_VER
#pragma warning(disable: 4290)
#define NOEXCEPT throw()

#ifdef LUPUSCORE_EXPORT
#define LUPUS_API __declspec(dllexport)
#else
#define LUPUS_API __declspec(dllimport)
#endif

#else
#define NOEXCEPT noexcept

#ifdef LUPUSCORE_EXPORT

#ifdef __CYGWIN__
#define LUPUS_API __attribute__ ((dllexport))
#else
#define LUPUS_API __attribute__ ((visibility ("default")))
#endif

#else

#ifdef __CYGWIN__
#define LUPUS_API __attribute__ ((dllimport))
#else
#define LUPUS_API __attribute__ ((visibility ("default")))
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

namespace Lupus {
    LupusDefineError(null_pointer);
    LupusDefineError(sql_error);
    LupusDefineError(socket_error);
    LupusDefineError(http_error);
    LupusDefineError(io_error);
    LupusDefineError(not_supported);
    LupusDefineError(unauthorized_access);
    LupusDefineError(authentication_error);

    LUPUS_API std::string RandomString(unsigned);

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
}
