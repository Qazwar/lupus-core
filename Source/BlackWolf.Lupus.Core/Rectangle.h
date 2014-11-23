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

#include "Size.h"
#include "Point.h"

namespace Lupus {
    namespace Math {
        // TODO: Rechteck ausbauen und implementieren.

        template <typename T>
        struct Rectangle
        {
            T X = T();
            T Y = T();
            T Width = T();
            T Height = T();

            Rectangle() = default;
            Rectangle(const Rectangle&) = default;
            Rectangle& operator=(const Rectangle&) = default;

            Rectangle(T x, T y, T w, T h)
            {
                X = x;
                Y = y;
                Width = w;
                Height = h;
            }

            Rectangle(const Math::Point<T>& p, const Math::Size<T>& size)
            {
                X = p.X;
                Y = p.Y;
                Width = size.Width;
                Height = size.Height;
            }

            T Left() const NOEXCEPT
            {
                return X;
            }

            T Right() const NOEXCEPT
            {
                return (X + Widht);
            }

            T Top() const NOEXCEPT
            {
                return Y;
            }

            T Bottom() const NOEXCEPT
            {
                return (Y + Height);
            }
            
            Point<T> TopLeft() const NOEXCEPT
            {
                return Point<T>(X, Y);
            }

            Point<T> TopRight() const NOEXCEPT
            {
                return Point<T>(Right(), Y);
            }

            Point<T> BottomLeft() const NOEXCEPT
            {
                return Point<T>(X, Bottom());
            }

            Point<T> BottomRight() const NOEXCEPT
            {
                return Point<T>(Right(), Bottom());
            }

            Point<T> Position() const NOEXCEPT
            {
                return TopLeft();
            }

            Math::Size<T> Size() const NOEXCEPT
            {
                return Math::Size<T>(X, Y);
            }

            bool Contains(const Point<T>& point) const NOEXCEPT
            {
                return false;
            }

            bool Contains(const Rectangle<T>& rect) const NOEXCEPT
            {
                return false;
            }

            bool Contains(T x, T y) const NOEXCEPT
            {
                return false;
            }

            String ToString() const
            {
                return (
                    Integer::ToString(X) + "," +
                    Integer::ToString(Y) + "," +
                    Integer::ToString(Width) + "," +
                    Integer::ToString(Height)
                );
            }
        };
    }
}
