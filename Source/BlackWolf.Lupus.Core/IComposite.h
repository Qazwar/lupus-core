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

#include <memory>
#include <unordered_set>

namespace Lupus {
    template <typename Component, typename Container = std::unordered_set<Component>>
    class IComposite : public Component
    {
    public:
        virtual ~IComposite() = default;

        virtual void Add(const Component& component) = 0;
        virtual void Clear() = 0;
        virtual void Remove(const Component& component) = 0;
        virtual const Container& Children() const = 0;
    };

    template <typename Component, typename Container = std::unordered_set<std::shared_ptr<Component>>>
    class ICompositeReference : public Component
    {
    public:
        virtual ~ICompositeReference() = default;

        virtual void Add(const std::shared_ptr<Component>& component) = 0;
        virtual void Clear() = 0;
        virtual void Remove(const std::shared_ptr<Component>& component) = 0;
        virtual const Container& Children() const = 0;
    };
}
