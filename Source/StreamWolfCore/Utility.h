#pragma once

#include <string>
#include <exception>

#include <cryptopp/cryptlib.h>

#ifdef _MSC_VER
#pragma warning(disable: 4290)
#define NOEXCEPT throw()

#ifdef STREAMWOLFCORE_EXPORT
#define SWC_API __declspec(dllexport)
#else
#define SWC_API __declspec(dllimport)
#endif

#else
#deifne NOEXCEPT noexcept

#ifdef STREAMWOLFCORE_EXPORT

#ifdef __CYGWIN__
#define SWC_API __attribute__ ((dllexport))
#else
#define SWC_API __attribute__ ((visibility ("default")))
#endif

#else

#ifdef __CYGWIN__
#define SWC_API __attribute__ ((dllimport))
#else
#define SWC_API __attribute__ ((visibility ("default")))
#endif

#endif
#endif

#define DefineError(cls) \
    class cls : public virtual std::exception \
    { \
        std::string mMessage; \
    public: \
        inline cls(const std::string& message = "") : mMessage(message) { } \
        virtual ~cls() = default; \
        cls& operator=(const cls&) = default; \
        virtual inline const char* what() const override { return mMessage.c_str(); } \
    }

namespace StreamWolf {
    DefineError(null_pointer);
    DefineError(sql_error);
    DefineError(socket_error);
    DefineError(http_error);
    DefineError(io_error);
    DefineError(not_supported);
    DefineError(unauthorized_access);
    DefineError(authentication_error);

    /*template <unsigned N>
    std::string RandomString()
    {
        static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        const size_t size = sizeof(alphanum);
        CryptoPP::RandomNumberGenerator rng;
        std::string str(N, ' ');

        if (N == 0) {
            return "";
        } else if (N >= 1) {
            str[0] = alphanum[rng.GenerateWord32() % (size - 10) + 10];
        }

        for (unsigned i = 1; i < N; i++) {
            str[i] = alphanum[rng.GenerateWord32() % size];
        }

        return str;
    }*/
    SWC_API std::string RandomString(unsigned);

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
