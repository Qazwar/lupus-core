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
