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
    namespace Graphic {
        class LUPUSGRAPHIC_API UIElement : public NonCopyable
        {
        public:
            virtual ~UIElement() = default;
        };

        class LUPUSGRAPHIC_API UIElementComposite : public ICompositeReference<UIElement>
        {
        public:
            virtual ~UIElementComposite() = default;

            virtual void Add(const Pointer<UIElement>& component) NOEXCEPT override;
            virtual void Clear() NOEXCEPT override;
            virtual void Remove(const Pointer<UIElement>& component) NOEXCEPT override;
            virtual const Set<Pointer<UIElement>>& Children() const NOEXCEPT override;

        private:
            Set<Pointer<UIElement>> mChildren;
        };
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
