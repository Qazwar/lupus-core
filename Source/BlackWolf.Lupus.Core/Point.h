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
#pragma once

#include "String.h"
#include "Integer.h"
#include "Float.h"

namespace Lupus {
    namespace Math {
        template <typename T>
        struct Point
        {
            T X = T();
            T Y = T();

            Point() = default;
            Point(const Point&) = default;
            Point& operator=(const Point&) = default;
            
            Point(T value)
            {
                X = Y = value;
            }

            Point(T x, T y)
            {
                X = x;
                Y = y;
            }

            String ToString() const
            {
                return (Integer::ToString(X) + "," + Integer::ToString(Y));
            }

            static Point Parse(const String& str) throw(FormatError)
            {
                auto index = str.IndexOf(",");
                auto x = str.Substring(0, index);
                auto y = str.Substring(index + 1);

                if (str.IndexOf(",", index + 1) != -1) {
                    throw FormatError("Invalid point string");
                }

                Point point;
                if (!Integer::TryParse(x, point.X) || !Integer::TryParse(y, point.Y)) {
                    throw FormatError("Invalid number");
                }

                return point;
            }

            bool operator==(const Point& other) const
            {
                return (X == other.X && Y == other.Y);
            }

            bool operator!=(const Point& other) const
            {
                return (X != other.X || Y != other.Y);
            }
        };

        template<>
        struct Point < float >
        {
            float X = 0;
            float Y = 0;

            Point() = default;
            Point(const Point&) = default;
            Point& operator=(const Point&) = default;

            Point(float value)
            {
                X = Y = value;
            }

            Point(float x, float y)
            {
                X = x;
                Y = y;
            }

            String ToString() const
            {
                return (Float::ToString(X) + "," + Float::ToString(Y));
            }

            static Point Parse(const String& str) throw(FormatError)
            {
                auto index = str.IndexOf(",");
                auto x = str.Substring(0, index);
                auto y = str.Substring(index + 1);

                if (str.IndexOf(",", index + 1) != -1) {
                    throw FormatError("Invalid point string");
                }

                Point point;
                if (!Float::TryParse(x, point.X) || !Float::TryParse(y, point.Y)) {
                    throw FormatError();
                }

                return point;
            }

            bool operator==(const Point& other) const
            {
                return (X == other.X && Y == other.Y);
            }

            bool operator!=(const Point& other) const
            {
                return (X != other.X || Y != other.Y);
            }
        };

        template<>
        struct Point < double >
        {
            double X = 0;
            double Y = 0;

            Point() = default;
            Point(const Point&) = default;
            Point& operator=(const Point&) = default;

            Point(double value)
            {
                X = Y = value;
            }

            Point(double x, double y)
            {
                X = x;
                Y = y;
            }

            String ToString() const
            {
                return (Float::ToString(X) + "," + Float::ToString(Y));
            }

            static Point Parse(const String& str) throw(FormatError)
            {
                auto index = str.IndexOf(",");
                auto x = str.Substring(0, index);
                auto y = str.Substring(index + 1);

                if (str.IndexOf(",", index + 1) != -1) {
                    throw FormatError("Invalid point string");
                }

                Point point;
                if (!Float::TryParse(x, point.X) || !Float::TryParse(y, point.Y)) {
                    throw FormatError();
                }

                return point;
            }

            bool operator==(const Point& other) const
            {
                return (X == other.X && Y == other.Y);
            }

            bool operator!=(const Point& other) const
            {
                return (X != other.X || Y != other.Y);
            }
        };

        template<>
        struct Point < long double >
        {
            long double X = 0;
            long double Y = 0;

            Point() = default;
            Point(const Point&) = default;
            Point& operator=(const Point&) = default;

            Point(long double value)
            {
                X = Y = value;
            }

            Point(long double x, long double y)
            {
                X = x;
                Y = y;
            }

            String ToString() const
            {
                return (Float::ToString(X) + "," + Float::ToString(Y));
            }

            static Point Parse(const String& str) throw(FormatError)
            {
                auto index = str.IndexOf(",");
                auto x = str.Substring(0, index);
                auto y = str.Substring(index + 1);

                if (str.IndexOf(",", index + 1) != -1) {
                    throw FormatError("Invalid point string");
                }

                Point point;
                if (!Float::TryParse(x, point.X) || !Float::TryParse(y, point.Y)) {
                    throw FormatError();
                }

                return point;
            }

            bool operator==(const Point& other) const
            {
                return (X == other.X && Y == other.Y);
            }

            bool operator!=(const Point& other) const
            {
                return (X != other.X || Y != other.Y);
            }
        };
    }
}
