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
#include "Float.h"
#include <cstdio>
#include <cstring>

#ifdef _MSC_VER
#define snprintf _snprintf_s
#define sscanf sscanf_s
#endif

namespace Lupus {
    static const size_t sFloatCount = 32;

	String Float::ToString(float value)
	{
		char result[sFloatCount];
		memset(result, 0, sFloatCount);
		snprintf(result, sFloatCount, ("%f"), value);
		return result;
	}

	String Float::ToString(double value)
	{
		char result[sFloatCount];
		memset(result, 0, sFloatCount);
        snprintf(result, sFloatCount, ("%lf"), value);
		return result;
	}
		
	String Float::ToString(long double value)
	{
		char result[sFloatCount];
		memset(result, 0, sFloatCount);
        snprintf(result, sFloatCount, ("%Lf"), value);
		return result;
	}

	bool Float::TryParse(const String& str, float& result)
	{
        return (sscanf(str.ToUTF8().c_str(), ("%f"), &result) == 1);
	}

	bool Float::TryParse(const String& str, double& result)
	{
        return (sscanf(str.ToUTF8().c_str(), ("%lf"), &result) == 1);
	}

	bool Float::TryParse(const String& str, long double& result)
	{
        return (sscanf(str.ToUTF8().c_str(), ("%Lf"), &result) == 1);
	}

    float Float::ParseFloat(const String& String)
    {
        float result = 0;

        if (!TryParse(String, result)) {
            throw std::invalid_argument("Could not parse given string to float");
        }

        return result;
    }
    
    double Float::ParseDouble(const String& String)
    {
        double result = 0;

        if (!TryParse(String, result)) {
            throw std::invalid_argument("Could not parse given string to float");
        }

        return result;
    }
    
    long double Float::ParseLongDouble(const String& String)
    {
        long double result = 0;

        if (!TryParse(String, result)) {
            throw std::invalid_argument("Could not parse given String to float");
        }

        return result;
    }
}
