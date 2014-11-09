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

#include "Utility.h"
#include <BlackWolf.Lupus.Core/Utility.h>
#include <BlackWolf.Lupus.Core/IComposite.h>
#include <boost/noncopyable.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Windows {
        class LUPUSWINDOWS_API UIElement : public boost::noncopyable
        {
        public:
            virtual ~UIElement() = default;
        };

        class LUPUSWINDOWS_API UIElementComposite : public ICompositeReference<UIElement>
        {
        public:
            virtual ~UIElementComposite() = default;

            virtual void Add(const std::shared_ptr<UIElement>& component) NOEXCEPT override;
            virtual void Clear() NOEXCEPT override;
            virtual void Remove(const std::shared_ptr<UIElement>& component) NOEXCEPT override;
            virtual const std::unordered_set<std::shared_ptr<UIElement>>& Children() const NOEXCEPT override;

        private:
            std::unordered_set<std::shared_ptr<UIElement>> mChildren;
        };
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
