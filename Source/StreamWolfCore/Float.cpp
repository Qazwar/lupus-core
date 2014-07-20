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

#include "Float.h"
#include <cstdio>
#include <cstring>

#ifdef _MSC_VER
#define snprintf_s _snprintf_s
#else
#define snprintf_s snprintf
#endif

namespace Lupus {
    static const size_t sFloatCount = 32;

	std::string Float::ToString(float value)
	{
		char result[sFloatCount];
		memset(result, 0, sFloatCount);
		snprintf_s(result, sFloatCount, ("%f"), value);
		return result;
	}

	std::string Float::ToString(double value)
	{
		char result[sFloatCount];
		memset(result, 0, sFloatCount);
        snprintf_s(result, sFloatCount, ("%lf"), value);
		return result;
	}
		
	std::string Float::ToString(long double value)
	{
		char result[sFloatCount];
		memset(result, 0, sFloatCount);
        snprintf_s(result, sFloatCount, ("%Lf"), value);
		return result;
	}

	bool Float::TryParse(const std::string& string, float& result)
	{
        return (sscanf_s(string.c_str(), ("%f"), &result) == 1);
	}

	bool Float::TryParse(const std::string& string, double& result)
	{
		return (sscanf_s(string.c_str(), ("%lf"), &result) == 1);
	}

	bool Float::TryParse(const std::string& string, long double& result)
	{
        return (sscanf_s(string.c_str(), ("%Lf"), &result) == 1);
	}

    float Float::ParseFloat(const std::string& string)
    {
        float result = 0;

        if (!TryParse(string, result)) {
            throw std::invalid_argument("could not parse given string to float");
        }

        return result;
    }
    
    double Float::ParseDouble(const std::string& string)
    {
        double result = 0;

        if (!TryParse(string, result)) {
            throw std::invalid_argument("could not parse given string to float");
        }

        return result;
    }
    
    long double Float::ParseLongDouble(const std::string& string)
    {
        long double result = 0;

        if (!TryParse(string, result)) {
            throw std::invalid_argument("could not parse given string to float");
        }

        return result;
    }
}
