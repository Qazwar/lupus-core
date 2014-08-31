#pragma once

#include "Utility.h"
#include "Integer.h"
#include "Float.h"

namespace Lupus {
    namespace Math {
        template <typename T>
        struct LUPUS_API Size
        {
            T Width = T();
            T Height = T();

            Size() = default;
            Size(const Size&) = default;
            Size& operator=(const Size&) = default;
            
            Size(T value)
            {
                Width = Height = value;
            }

            Size(T width, T height)
            {
                Width = width;
                Height = height;
            }

            std::string ToString() const
            {
                return (Integer::ToString(Width) + "," + Integer::ToString(Height));
            }

            static Size Parse(const std::string& string) throw(format_error)
            {
                auto index = string.find_first_of(',');
                auto width = string.substr(0, index);
                auto height = string.substr(index + 1);

                if (index != string.find_last_not_of(',')) {
                    throw format_error();
                }

                Size size;
                if (!Integer::TryParse(width, size.Width) || !Integer::TryParse(height, size.Height)) {
                    throw format_error();
                }

                return size;
            }

            bool operator==(const Size& other) const
            {
                return (Width == other.Width && Height == other.Height);
            }

            bool operator!=(const Size& other) const
            {
                return (Width != other.Width || Height != other.Height);
            }
        };

        template <>
        struct LUPUS_API Size < float >
        {
            float Width = 0;
            float Height = 0;

            Size() = default;
            Size(const Size&) = default;
            Size& operator=(const Size&) = default;

            Size(float value)
            {
                Width = Height = value;
            }

            Size(float width, float height)
            {
                Width = width;
                Height = height;
            }

            std::string ToString() const
            {
                return (Float::ToString(Width) + "," + Float::ToString(Height));
            }

            static Size Parse(const std::string& string) throw(format_error)
            {
                auto index = string.find_first_of(',');
                auto width = string.substr(0, index);
                auto height = string.substr(index);

                if (index != string.find_last_not_of(',')) {
                    throw format_error();
                }

                Size size;
                if (!Float::TryParse(width, size.Width) || !Float::TryParse(height, size.Height)) {
                    throw format_error();
                }

                return size;
            }

            bool operator==(const Size& other) const
            {
                return (Width == other.Width && Height == other.Height);
            }

            bool operator!=(const Size& other) const
            {
                return (Width != other.Width || Height != other.Height);
            }
        };

        template <>
        struct LUPUS_API Size < double >
        {
            double Width = 0;
            double Height = 0;

            Size() = default;
            Size(const Size&) = default;
            Size& operator=(const Size&) = default;

            Size(double value)
            {
                Width = Height = value;
            }

            Size(double width, double height)
            {
                Width = width;
                Height = height;
            }

            std::string ToString() const
            {
                return (Float::ToString(Width) + "," + Float::ToString(Height));
            }

            static Size Parse(const std::string& string) throw(format_error)
            {
                auto index = string.find_first_of(',');
                auto width = string.substr(0, index);
                auto height = string.substr(index);

                if (index != string.find_last_not_of(',')) {
                    throw format_error();
                }

                Size size;
                if (!Float::TryParse(width, size.Width) || !Float::TryParse(height, size.Height)) {
                    throw format_error();
                }

                return size;
            }

            bool operator==(const Size& other) const
            {
                return (Width == other.Width && Height == other.Height);
            }

            bool operator!=(const Size& other) const
            {
                return (Width != other.Width || Height != other.Height);
            }
        };

        template <>
        struct LUPUS_API Size < long double >
        {
            long double Width = 0;
            long double Height = 0;

            Size() = default;
            Size(const Size&) = default;
            Size& operator=(const Size&) = default;

            Size(long double value)
            {
                Width = Height = value;
            }

            Size(long double width, long double height)
            {
                Width = width;
                Height = height;
            }

            std::string ToString() const
            {
                return (Float::ToString(Width) + "," + Float::ToString(Height));
            }

            static Size Parse(const std::string& string) throw(format_error)
            {
                auto index = string.find_first_of(',');
                auto width = string.substr(0, index);
                auto height = string.substr(index);

                if (index != string.find_last_not_of(',')) {
                    throw format_error();
                }

                Size size;
                if (!Float::TryParse(width, size.Width) || !Float::TryParse(height, size.Height)) {
                    throw format_error();
                }

                return size;
            }

            bool operator==(const Size& other) const
            {
                return (Width == other.Width && Height == other.Height);
            }

            bool operator!=(const Size& other) const
            {
                return (Width != other.Width || Height != other.Height);
            }
        };
    }
}
