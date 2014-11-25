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
#include "Float.h"
#include <cstdio>
#include <cstring>

#ifdef _MSC_VER
#define snprintf _snprintf_s
#define sscanf sscanf_s
#endif

namespace Lupus {
    static const U32 sFloatCount = 32;

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

    float Float::ParseFloat(const String& str)
    {
        float result = 0;

        if (!TryParse(str, result)) {
            throw InvalidArgument("str");
        }

        return result;
    }
    
    double Float::ParseDouble(const String& str)
    {
        double result = 0;

        if (!TryParse(str, result)) {
            throw InvalidArgument("str");
        }

        return result;
    }
    
    long double Float::ParseLongDouble(const String& str)
    {
        long double result = 0;

        if (!TryParse(str, result)) {
            throw InvalidArgument("str");
        }

        return result;
    }
}
