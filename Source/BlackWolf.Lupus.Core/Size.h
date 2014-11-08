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
#pragma once

#include "String.h"
#include "Integer.h"
#include "Float.h"

namespace Lupus {
    namespace Math {
        template <typename T>
        struct Size
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

            String ToString() const
            {
                return (Integer::ToString(Width) + "," + Integer::ToString(Height));
            }

            static Size Parse(const String& str) throw(format_error)
            {
                auto index = str.IndexOf(",");
                auto width = str.Substring(0, index);
                auto height = str.Substring(index + 1);

                if (str.IndexOf(",", index + 1) != -1) {
                    throw format_error("Invalid point string");
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
        struct Size < float >
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

            String ToString() const
            {
                return (Float::ToString(Width) + "," + Float::ToString(Height));
            }

            static Size Parse(const String& str) throw(format_error)
            {
                auto index = str.IndexOf(",");
                auto width = str.Substring(0, index);
                auto height = str.Substring(index + 1);

                if (str.IndexOf(",", index + 1) != -1) {
                    throw format_error("Invalid point string");
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
        struct Size < double >
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

            String ToString() const
            {
                return (Float::ToString(Width) + "," + Float::ToString(Height));
            }

            static Size Parse(const String& str) throw(format_error)
            {
                auto index = str.IndexOf(",");
                auto width = str.Substring(0, index);
                auto height = str.Substring(index + 1);

                if (str.IndexOf(",", index + 1) != -1) {
                    throw format_error("Invalid point string");
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
        struct Size < long double >
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

            String ToString() const
            {
                return (Float::ToString(Width) + "," + Float::ToString(Height));
            }

            static Size Parse(const String& str) throw(format_error)
            {
                auto index = str.IndexOf(",");
                auto width = str.Substring(0, index);
                auto height = str.Substring(index + 1);

                if (str.IndexOf(",", index + 1) != -1) {
                    throw format_error("Invalid point string");
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
