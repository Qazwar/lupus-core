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
#include "Integer.h"
#include <cstdio>
#include <cstring>

#ifdef _MSC_VER
#define snprintf _snprintf_s
#define sscanf sscanf_s
#endif

namespace Lupus {
    static const U32 sIntegerCount = 32;

    String Integer::ToString(S8 value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf(result, sIntegerCount, ("%hhd"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf(result, sIntegerCount, ("%#hhx"), value);
                break;
            case IntegerBase::Octal:
                snprintf(result, sIntegerCount, ("%#hho"), value);
                break;
        }
        return result;
    }

    String Integer::ToString(short value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf(result, sIntegerCount, ("%hd"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf(result, sIntegerCount, ("%#hx"), value);
                break;
            case IntegerBase::Octal:
                snprintf(result, sIntegerCount, ("%#ho"), value);
                break;
        }
        return result;
    }

    String Integer::ToString(int value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf(result, sIntegerCount, ("%d"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf(result, sIntegerCount, ("%#x"), value);
                break;
            case IntegerBase::Octal:
                snprintf(result, sIntegerCount, ("%#o"), value);
                break;
        }
        return result;
    }

    String Integer::ToString(long value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf(result, sIntegerCount, ("%ld"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf(result, sIntegerCount, ("%#lx"), value);
                break;
            case IntegerBase::Octal:
                snprintf(result, sIntegerCount, ("%#lo"), value);
                break;
        }
        return result;
    }

    String Integer::ToString(long long value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf(result, sIntegerCount, ("%lld"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf(result, sIntegerCount, ("%#llx"), value);
                break;
            case IntegerBase::Octal:
                snprintf(result, sIntegerCount, ("%#llo"), value);
                break;
        }
        return result;
    }

    String Integer::ToString(U8 value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf(result, sIntegerCount, ("%hhu"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf(result, sIntegerCount, ("%#hhx"), value);
                break;
            case IntegerBase::Octal:
                snprintf(result, sIntegerCount, ("%#hho"), value);
                break;
        }
        return result;
    }

    String Integer::ToString(unsigned short value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf(result, sIntegerCount, ("%hu"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf(result, sIntegerCount, ("%#hx"), value);
                break;
            case IntegerBase::Octal:
                snprintf(result, sIntegerCount, ("%#ho"), value);
                break;
        }
        return result;
    }

    String Integer::ToString(unsigned int value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf(result, sIntegerCount, ("%u"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf(result, sIntegerCount, ("%#x"), value);
                break;
            case IntegerBase::Octal:
                snprintf(result, sIntegerCount, ("%#o"), value);
                break;
        }
        return result;
    }

    String Integer::ToString(unsigned long value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf(result, sIntegerCount, ("%lu"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf(result, sIntegerCount, ("%#lx"), value);
                break;
            case IntegerBase::Octal:
                snprintf(result, sIntegerCount, ("%#lo"), value);
                break;
        }
        return result;
    }

    String Integer::ToString(unsigned long long value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf(result, sIntegerCount, ("%llu"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf(result, sIntegerCount, ("%#llx"), value);
                break;
            case IntegerBase::Octal:
                snprintf(result, sIntegerCount, ("%#llo"), value);
                break;
        }
        return result;
    }

    bool Integer::TryParse(const String& str, S8& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf(str.ToUTF8().c_str(), ("%hhd"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf(str.ToUTF8().c_str(), ("%hhx"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf(str.ToUTF8().c_str(), ("%hho"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const String& str, short& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf(str.ToUTF8().c_str(), ("%hd"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf(str.ToUTF8().c_str(), ("%hx"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf(str.ToUTF8().c_str(), ("%ho"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const String& str, int& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf(str.ToUTF8().c_str(), ("%d"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf(str.ToUTF8().c_str(), ("%x"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf(str.ToUTF8().c_str(), ("%o"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const String& str, long& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf(str.ToUTF8().c_str(), ("%ld"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf(str.ToUTF8().c_str(), ("%lx"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf(str.ToUTF8().c_str(), ("%lo"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const String& str, long long& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf(str.ToUTF8().c_str(), ("%lld"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf(str.ToUTF8().c_str(), ("%llx"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf(str.ToUTF8().c_str(), ("%llo"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const String& str, U8& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf(str.ToUTF8().c_str(), ("%hhu"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf(str.ToUTF8().c_str(), ("%hhx"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf(str.ToUTF8().c_str(), ("%hho"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const String& str, unsigned short& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf(str.ToUTF8().c_str(), ("%hu"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf(str.ToUTF8().c_str(), ("%hx"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf(str.ToUTF8().c_str(), ("%ho"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const String& str, unsigned int& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf(str.ToUTF8().c_str(), ("%u"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf(str.ToUTF8().c_str(), ("%x"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf(str.ToUTF8().c_str(), ("%o"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const String& str, unsigned long& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf(str.ToUTF8().c_str(), ("%lu"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf(str.ToUTF8().c_str(), ("%lx"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf(str.ToUTF8().c_str(), ("%lo"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const String& str, unsigned long long& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf(str.ToUTF8().c_str(), ("%llu"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf(str.ToUTF8().c_str(), ("%llx"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf(str.ToUTF8().c_str(), ("%llo"), &result) == 1);
        }
        return false;
    }

    S8 Integer::ParseByte(const String& str, IntegerBase base)
    {
        S8 result = 0;

        if (!TryParse(str, result, base)) {
            throw InvalidArgument("str");
        }

        return result;
    }

    short Integer::ParseShort(const String& str, IntegerBase base)
    {
        short result = 0;

        if (!TryParse(str, result, base)) {
            throw InvalidArgument("str");
        }

        return result;
    }

    int Integer::ParseInt(const String& str, IntegerBase base)
    {
        int result = 0;

        if (!TryParse(str, result, base)) {
            throw InvalidArgument("str");
        }

        return result;
    }

    long Integer::ParseLong(const String& str, IntegerBase base)
    {
        long result = 0;

        if (!TryParse(str, result, base)) {
            throw InvalidArgument("str");
        }

        return result;
    }

    long long Integer::ParseLongLong(const String& str, IntegerBase base)
    {
        long long result = 0;

        if (!TryParse(str, result, base)) {
            throw InvalidArgument("str");
        }

        return result;
    }

    U8 Integer::ParseUByte(const String& str, IntegerBase base)
    {
        U8 result = 0;

        if (!TryParse(str, result, base)) {
            throw InvalidArgument("str");
        }

        return result;
    }

    unsigned short Integer::ParseUShort(const String& str, IntegerBase base)
    {
        unsigned short result = 0;

        if (!TryParse(str, result, base)) {
            throw InvalidArgument("str");
        }

        return result;
    }

    unsigned int Integer::ParseUInt(const String& str, IntegerBase base)
    {
        unsigned int result = 0;

        if (!TryParse(str, result, base)) {
            throw InvalidArgument("str");
        }

        return result;
    }

    unsigned long Integer::ParseULong(const String& str, IntegerBase base)
    {
        unsigned long result = 0;

        if (!TryParse(str, result, base)) {
            throw InvalidArgument("str");
        }

        return result;
    }

    unsigned long long Integer::ParseULongLong(const String& str, IntegerBase base)
    {
        unsigned long long result = 0;

        if (!TryParse(str, result, base)) {
            throw InvalidArgument("str");
        }

        return result;
    }
}
