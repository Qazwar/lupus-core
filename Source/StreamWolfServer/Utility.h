#pragma once

#include <string>
#include <exception>

#include <cryptopp/cryptlib.h>

#ifdef _MSC_VER
#pragma warning(disable: 4290)
#define NOEXCEPT throw()
#else
#deifne NOEXCEPT noexcept
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

    template <unsigned N>
    tstring RandomString()
    {
        static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        const size_t size = sizeof(alphanum);
        CryptoPP::RandomNumberGenerator rng;
        tstring str(N, ' ');

        for (unsigned i = 0; i < N; i++) {
            str[i] = alphanum[rng.GenerateWord32() % size];
        }

        return str;
    }

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
