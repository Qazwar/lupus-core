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
#include <functional>
#include <boost/noncopyable.hpp>

#include "String.h"
#include "Task.h"
#include "IsolationLevel.h"

namespace Lupus {
    namespace Data {
        class ITransaction;
        class Command;

        class LUPUSCORE_API Connection : public boost::noncopyable
        {
        public:
            
            virtual ~Connection() = default;

            virtual Task<std::shared_ptr<ITransaction>> BeginTransactionAsync(IsolationLevel) throw(std::invalid_argument);
            virtual Task<void> ConnectAsync(const String&) throw(std::invalid_argument);

            virtual String ConnectionString() const NOEXCEPT = 0;
            
            virtual std::shared_ptr<ITransaction> BeginTransaction(IsolationLevel = IsolationLevel::Committed) throw(sql_error) = 0;
            virtual void Connect(const String&) throw(sql_error) = 0;
            virtual void Close() NOEXCEPT = 0;
            virtual std::shared_ptr<Command> CreateCommand() throw(sql_error) = 0;
            virtual void Open() throw(sql_error) = 0;
        };
    }
}
