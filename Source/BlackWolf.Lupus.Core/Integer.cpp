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
#include "Integer.h"
#include <cstdio>
#include <cstring>

#ifdef _MSC_VER
#define snprintf _snprintf_s
#define sscanf sscanf_s
#endif

namespace Lupus {
    static const size_t sIntegerCount = 32;

    String Integer::ToString(int8_t value, IntegerBase base)
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

    String Integer::ToString(uint8_t value, IntegerBase base)
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

    bool Integer::TryParse(const String& str, int8_t& result, IntegerBase base)
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

    bool Integer::TryParse(const String& str, uint8_t& result, IntegerBase base)
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

    int8_t Integer::ParseByte(const String& str, IntegerBase base)
    {
        int8_t result = 0;

        if (!TryParse(str, result, base)) {
            throw std::invalid_argument("Could not parse String to integer");
        }

        return result;
    }

    short Integer::ParseShort(const String& str, IntegerBase base)
    {
        short result = 0;

        if (!TryParse(str, result, base)) {
            throw std::invalid_argument("Could not parse String to integer");
        }

        return result;
    }

    int Integer::ParseInt(const String& str, IntegerBase base)
    {
        int result = 0;

        if (!TryParse(str, result, base)) {
            throw std::invalid_argument("Could not parse String to integer");
        }

        return result;
    }

    long Integer::ParseLong(const String& str, IntegerBase base)
    {
        long result = 0;

        if (!TryParse(str, result, base)) {
            throw std::invalid_argument("Could not parse String to integer");
        }

        return result;
    }

    long long Integer::ParseLongLong(const String& str, IntegerBase base)
    {
        long long result = 0;

        if (!TryParse(str, result, base)) {
            throw std::invalid_argument("Could not parse String to integer");
        }

        return result;
    }

    uint8_t Integer::ParseUByte(const String& str, IntegerBase base)
    {
        uint8_t result = 0;

        if (!TryParse(str, result, base)) {
            throw std::invalid_argument("Could not parse String to integer");
        }

        return result;
    }

    unsigned short Integer::ParseUShort(const String& str, IntegerBase base)
    {
        unsigned short result = 0;

        if (!TryParse(str, result, base)) {
            throw std::invalid_argument("Could not parse String to integer");
        }

        return result;
    }

    unsigned int Integer::ParseUInt(const String& str, IntegerBase base)
    {
        unsigned int result = 0;

        if (!TryParse(str, result, base)) {
            throw std::invalid_argument("Could not parse String to integer");
        }

        return result;
    }

    unsigned long Integer::ParseULong(const String& str, IntegerBase base)
    {
        unsigned long result = 0;

        if (!TryParse(str, result, base)) {
            throw std::invalid_argument("Could not parse String to integer");
        }

        return result;
    }

    unsigned long long Integer::ParseULongLong(const String& str, IntegerBase base)
    {
        unsigned long long result = 0;

        if (!TryParse(str, result, base)) {
            throw std::invalid_argument("Could not parse String to integer");
        }

        return result;
    }
}
