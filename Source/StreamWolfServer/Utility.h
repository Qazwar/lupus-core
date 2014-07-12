#pragma once

#include <string>
#include <cryptopp/cryptlib.h>

namespace StreamWolf {
    template <unsigned N>
    std::string RandomString()
    {
        static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        const size_t size = sizeof(alphanum);
        CryptoPP::RandomNumberGenerator rng;
        std::string str(N, ' ');

        for (unsigned i = 0; i < N; i++) {
            str[i] = alphanum[rng.GenerateWord32() % size];
        }

        return str;
    }
}
