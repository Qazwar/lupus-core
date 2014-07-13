/* Copyright © 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of LupusFramwork.
 *
 * LupusFramwork is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LupusFramwork is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LupusFramwork.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Integer.hpp"
#include <cstdio>
#include <cstring>

#ifdef _MSC_VER
#define snprintf_s _snprintf_s
#endif

namespace StreamWolf {
    static const size_t sIntegerCount = 32;

    std::string Integer::ToString(int8_t value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf_s(result, sIntegerCount, ("%hhd"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf_s(result, sIntegerCount, ("%#hhx"), value);
                break;
            case IntegerBase::Octal:
                snprintf_s(result, sIntegerCount, ("%#hho"), value);
                break;
        }
        return result;
    }

    std::string Integer::ToString(short value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf_s(result, sIntegerCount, ("%hd"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf_s(result, sIntegerCount, ("%#hx"), value);
                break;
            case IntegerBase::Octal:
                snprintf_s(result, sIntegerCount, ("%#ho"), value);
                break;
        }
        return result;
    }

    std::string Integer::ToString(int value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf_s(result, sIntegerCount, ("%d"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf_s(result, sIntegerCount, ("%#x"), value);
                break;
            case IntegerBase::Octal:
                snprintf_s(result, sIntegerCount, ("%#o"), value);
                break;
        }
        return result;
    }

    std::string Integer::ToString(long value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf_s(result, sIntegerCount, ("%ld"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf_s(result, sIntegerCount, ("%#lx"), value);
                break;
            case IntegerBase::Octal:
                snprintf_s(result, sIntegerCount, ("%#lo"), value);
                break;
        }
        return result;
    }

    std::string Integer::ToString(long long value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf_s(result, sIntegerCount, ("%lld"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf_s(result, sIntegerCount, ("%#llx"), value);
                break;
            case IntegerBase::Octal:
                snprintf_s(result, sIntegerCount, ("%#llo"), value);
                break;
        }
        return result;
    }

    std::string Integer::ToString(uint8_t value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf_s(result, sIntegerCount, ("%hhu"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf_s(result, sIntegerCount, ("%#hhx"), value);
                break;
            case IntegerBase::Octal:
                snprintf_s(result, sIntegerCount, ("%#hho"), value);
                break;
        }
        return result;
    }

    std::string Integer::ToString(unsigned short value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf_s(result, sIntegerCount, ("%hu"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf_s(result, sIntegerCount, ("%#hx"), value);
                break;
            case IntegerBase::Octal:
                snprintf_s(result, sIntegerCount, ("%#ho"), value);
                break;
        }
        return result;
    }

    std::string Integer::ToString(unsigned int value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf_s(result, sIntegerCount, ("%u"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf_s(result, sIntegerCount, ("%#x"), value);
                break;
            case IntegerBase::Octal:
                snprintf_s(result, sIntegerCount, ("%#o"), value);
                break;
        }
        return result;
    }

    std::string Integer::ToString(unsigned long value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf_s(result, sIntegerCount, ("%lu"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf_s(result, sIntegerCount, ("%#lx"), value);
                break;
            case IntegerBase::Octal:
                snprintf_s(result, sIntegerCount, ("%#lo"), value);
                break;
        }
        return result;
    }

    std::string Integer::ToString(unsigned long long value, IntegerBase base)
    {
        char result[sIntegerCount];
        memset(result, 0, sIntegerCount);

        switch (base) {
            case IntegerBase::Decimal:
                snprintf_s(result, sIntegerCount, ("%llu"), value);
                break;
            case IntegerBase::Hexadecimal:
                snprintf_s(result, sIntegerCount, ("%#llx"), value);
                break;
            case IntegerBase::Octal:
                snprintf_s(result, sIntegerCount, ("%#llo"), value);
                break;
        }
        return result;
    }

    bool Integer::TryParse(const std::string& string, int8_t& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf_s(string.c_str(), ("%hhd"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf_s(string.c_str(), ("%hhx"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf_s(string.c_str(), ("%hho"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const std::string& string, short& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf_s(string.c_str(), ("%hd"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf_s(string.c_str(), ("%hx"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf_s(string.c_str(), ("%ho"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const std::string& string, int& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf_s(string.c_str(), ("%d"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf_s(string.c_str(), ("%x"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf_s(string.c_str(), ("%o"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const std::string& string, long& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf_s(string.c_str(), ("%ld"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf_s(string.c_str(), ("%lx"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf_s(string.c_str(), ("%lo"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const std::string& string, long long& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf_s(string.c_str(), ("%lld"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf_s(string.c_str(), ("%llx"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf_s(string.c_str(), ("%llo"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const std::string& string, uint8_t& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf_s(string.c_str(), ("%hhu"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf_s(string.c_str(), ("%hhx"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf_s(string.c_str(), ("%hho"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const std::string& string, unsigned short& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf_s(string.c_str(), ("%hu"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf_s(string.c_str(), ("%hx"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf_s(string.c_str(), ("%ho"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const std::string& string, unsigned int& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf_s(string.c_str(), ("%u"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf_s(string.c_str(), ("%x"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf_s(string.c_str(), ("%o"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const std::string& string, unsigned long& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf_s(string.c_str(), ("%lu"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf_s(string.c_str(), ("%lx"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf_s(string.c_str(), ("%lo"), &result) == 1);
        }
        return false;
    }

    bool Integer::TryParse(const std::string& string, unsigned long long& result, IntegerBase base)
    {
        switch (base) {
            case IntegerBase::Decimal:
                return (sscanf_s(string.c_str(), ("%llu"), &result) == 1);
            case IntegerBase::Hexadecimal:
                return (sscanf_s(string.c_str(), ("%llx"), &result) == 1);
            case IntegerBase::Octal:
                return (sscanf_s(string.c_str(), ("%llo"), &result) == 1);
        }
        return false;
    }
}
