#pragma once

#include "Utility.h"
#include "Integer.h"
#include "Float.h"

namespace Lupus {
    namespace Math {
        template <typename T>
        struct LUPUS_API Point
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

            std::string ToString() const
            {
                return (Integer::ToString(X) + "," + Integer::ToString(Y));
            }

            static Point Parse(const std::string& string) throw(format_error)
            {
                auto index = string.find_first_of(',');
                auto x = string.substr(0, index);
                auto y = string.substr(index);

                if (index != string.find_last_not_of(',')) {
                    throw format_error();
                }

                Point point;
                if (!Integer::TryParse(x, point.X) || !Integer::TryParse(y, point.Y)) {
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
        struct LUPUS_API Point < float >
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

            std::string ToString() const
            {
                return (Float::ToString(X) + "," + Float::ToString(Y));
            }

            static Point Parse(const std::string& string) throw(format_error)
            {
                auto index = string.find_first_of(',');
                auto x = string.substr(0, index);
                auto y = string.substr(index);

                if (index != string.find_last_not_of(',')) {
                    throw format_error();
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
        struct LUPUS_API Point < double >
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

            std::string ToString() const
            {
                return (Float::ToString(X) + "," + Float::ToString(Y));
            }

            static Point Parse(const std::string& string) throw(format_error)
            {
                auto index = string.find_first_of(',');
                auto x = string.substr(0, index);
                auto y = string.substr(index);

                if (index != string.find_last_not_of(',')) {
                    throw format_error();
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
        struct LUPUS_API Point < long double >
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

            std::string ToString() const
            {
                return (Float::ToString(X) + "," + Float::ToString(Y));
            }

            static Point Parse(const std::string& string) throw(format_error)
            {
                auto index = string.find_first_of(',');
                auto x = string.substr(0, index);
                auto y = string.substr(index);

                if (index != string.find_last_not_of(',')) {
                    throw format_error();
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
