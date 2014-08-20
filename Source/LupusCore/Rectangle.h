#pragma once

#include "Size.h"
#include "Point.h"

namespace Lupus {
    namespace Math {
        // TODO: Rechteck ausbauen und implementieren

        template <typename T>
        struct LUPUS_API Rectangle
        {
            T X;
            T Y;
            T Width;
            T Height;

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

            Math::Size<T> Size() const NOEXCEPT
            {
                return Math::Size<T>(X, Y);
            }

            bool Contains(const Point<T>& point) const NOEXCEPT
            {
            }

            bool Contains(const Rectangle<T>& rect) const NOEXCEPT
            {
            }

            bool Contains(T x, T y) const NOEXCEPT
            {
            }

            std::string ToString() const
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
