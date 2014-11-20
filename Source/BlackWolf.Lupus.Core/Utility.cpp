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
#include "Utility.h"
#include "Version.h"
#include "String.h"

#include <cryptopp/osrng.h>
#include <unicode/uchar.h>

#ifdef _MSC_VER
#include <Windows.h>
#else
#endif

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

#ifdef _MSC_VER
    std::string GetLastSystemError()
    {
        CHAR buffer[1024];
        DWORD dw = GetLastError();
        memset(buffer, 0, 1024);

        FormatMessageA(
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            buffer,
            1023, NULL);

        return buffer;
    }
#else
    std::string GetLastSystemError()
    {
        return std::strerror(errno);
    }
#endif
}
