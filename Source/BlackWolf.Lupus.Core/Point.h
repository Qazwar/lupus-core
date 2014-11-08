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

            static Point Parse(const String& str) throw(format_error)
            {
                auto index = str.IndexOf(",");
                auto x = str.Substring(0, index);
                auto y = str.Substring(index + 1);

                if (str.IndexOf(",", index + 1) != -1) {
                    throw format_error("Invalid point string");
                }

                Point point;
                if (!Integer::TryParse(x, point.X) || !Integer::TryParse(y, point.Y)) {
                    throw format_error("Invalid number");
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

            static Point Parse(const String& str) throw(format_error)
            {
                auto index = str.IndexOf(",");
                auto x = str.Substring(0, index);
                auto y = str.Substring(index + 1);

                if (str.IndexOf(",", index + 1) != -1) {
                    throw format_error("Invalid point string");
                }

                Point point;
                if (!Float::TryParse(x, point.X) || !Float::TryParse(y, point.Y)) {
                    throw format_error();
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

            static Point Parse(const String& str) throw(format_error)
            {
                auto index = str.IndexOf(",");
                auto x = str.Substring(0, index);
                auto y = str.Substring(index + 1);

                if (str.IndexOf(",", index + 1) != -1) {
                    throw format_error("Invalid point string");
                }

                Point point;
                if (!Float::TryParse(x, point.X) || !Float::TryParse(y, point.Y)) {
                    throw format_error();
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

            static Point Parse(const String& str) throw(format_error)
            {
                auto index = str.IndexOf(",");
                auto x = str.Substring(0, index);
                auto y = str.Substring(index + 1);

                if (str.IndexOf(",", index + 1) != -1) {
                    throw format_error("Invalid point string");
                }

                Point point;
                if (!Float::TryParse(x, point.X) || !Float::TryParse(y, point.Y)) {
                    throw format_error();
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
