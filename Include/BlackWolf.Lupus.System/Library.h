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
#include <functional>
#include <boost/noncopyable.hpp>
#include <BlackWolf.Lupus.Core/String.h>

namespace Lupus {
    namespace System {
        class LUPUSSYSTEM_API Library : public boost::noncopyable
        {
        public:
            Library(String path) throw(io_error);
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
