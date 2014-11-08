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
