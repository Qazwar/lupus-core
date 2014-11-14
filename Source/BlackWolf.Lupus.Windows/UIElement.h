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
