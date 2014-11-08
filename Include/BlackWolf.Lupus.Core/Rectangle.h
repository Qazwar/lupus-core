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
