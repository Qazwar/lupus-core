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
#include "Utility.h"
#include "Version.h"
#include "String.h"

#include <cryptopp/osrng.h>
#include <unicode/uchar.h>

using namespace std;

namespace Lupus {
    String RandomString(uint32_t N)
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
        static const shared_ptr<Version> sVersion = make_shared<Version>(0, 1);
        return sVersion;
    }
}
