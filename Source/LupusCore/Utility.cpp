#include "Utility.h"
#include "Version.h"
#include "String.h"

#include <cryptopp/osrng.h>
#include <unicode/uchar.h>

using namespace std;

namespace Lupus {
    String RandomString(unsigned N)
    {
        const String alphanum("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
        const size_t size = alphanum.Length();
        CryptoPP::AutoSeededRandomPool rng;
        String str(' ' , N);

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

    shared_ptr<Version> GetVersion()
    {
        static const int32_t sMajor = 0;
        static const int32_t sMinor = 1;
        static const int32_t sBuild = 0;
        static const int32_t sRevision = 105;
        static const shared_ptr<Version> sVersion = make_shared<Version>(sMajor, sMinor, sBuild, sRevision);
        return sVersion;
    }
}
