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

#include <vector>
#include <algorithm>
#include <functional>

#include "Utility.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    template <typename Sender, typename... Args>
    class Event : public NonCopyable
    {
        friend Sender;

    public:

        typedef std::function<void(Sender*, Args...)> Handle;

        Event() = default;
        ~Event() = default;
        Event(Event&&) = delete;
        Event& operator=(Event&&) = delete;

        void Add(Handle&& f)
        {
            mCallbacks.push_back(f);
        }

        void Clear()
        {
            mCallbacks.clear();
        }

        Event& operator+=(Handle&& f)
        {
            mCallbacks.push_back(f);
            return *this;
        }

    private:

        void operator()(Sender* sender, Args&&... args)
        {
            std::for_each(std::begin(mCallbacks), std::end(mCallbacks), [&](Handle& callback) {
                callback(sender, std::forward<Args>(args)...);
            });
        }

        Vector<Handle> mCallbacks = Vector<Handle>(32);
    };

    template <typename... Args>
    class Event < void, Args... > : public NonCopyable
    {
    public:

        typedef std::function<void(Args...)> Handle;

        Event() = default;
        ~Event() = default;
        Event(Event&&) = delete;
        Event& operator=(Event&&) = delete;

        void Add(Handle&& f)
        {
            mCallbacks.push_back(f);
        }

        void Clear()
        {
            mCallbacks.clear();
        }

        Event& operator+=(Handle&& f)
        {
            mCallbacks.push_back(f);
            return *this;
        }

        void operator()(const Args&... args)
        {
            std::for_each(std::begin(mCallbacks), std::end(mCallbacks), [&](Handle& callback) {
                callback(args...);
            });
        }

    private:

        Vector<Handle> mCallbacks = Vector<Handle>(32);
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
