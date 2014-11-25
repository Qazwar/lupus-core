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
#include <functional>
#include <boost/noncopyable.hpp>
#include <BlackWolf.Lupus.Core/String.h>

namespace Lupus {
    namespace System {
        class LUPUSSYSTEM_API Library : public boost::noncopyable
        {
        public:
            Library(String path) throw(IOError);
            virtual ~Library();
            virtual void* GetFunctionHandle(String functionName) NOEXCEPT;

            template <typename ReturnType, typename... Args>
            std::function<ReturnType(Args...)> GetFunction(String functionName) NOEXCEPT
            {
                return std::function<ReturnType(Args...)>((ReturnType(*)(Args...))(GetFunctionHandle(functionName)));
            }

        private:

            uintptr_t mHandle = 0;
        };
    }
}
