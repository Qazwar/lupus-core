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

#include <vector>
#include <algorithm>
#include <functional>

#include "Utility.h"
#include <boost/noncopyable.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    template <typename Sender, typename... Args>
    class Event : public boost::noncopyable
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

        std::vector<Handle> mCallbacks = std::vector<Handle>(32);
    };

    template <typename... Args>
    class Event < void, Args... > : public boost::noncopyable
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

        void operator()(Args&&... args)
        {
            std::for_each(std::begin(mCallbacks), std::end(mCallbacks), [&](Handle& callback) {
                callback(std::forward<Args>(args)...);
            });
        }

    private:

        std::vector<Handle> mCallbacks = std::vector<Handle>(32);
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
