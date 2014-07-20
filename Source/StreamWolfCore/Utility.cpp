#include "Utility.h"

#include <cryptopp/cryptlib.h>

using namespace std;

namespace StreamWolf {
    string RandomString(unsigned N)
    {
        static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        const size_t size = sizeof(alphanum);
        CryptoPP::RandomNumberGenerator rng;
        string str(N, ' ');

        if (N == 0) {
            return "";
        } else if (N >= 1) {
            str[0] = alphanum[rng.GenerateWord32() % (size - 10) + 10];
        }

        for (unsigned i = 1; i < N; i++) {
            str[i] = alphanum[rng.GenerateWord32() % size];
        }

        return str;
    }
}
