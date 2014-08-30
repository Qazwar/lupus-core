#pragma once

#include <string>
#include <memory>
#include <functional>
#include <boost/noncopyable.hpp>

#include "Utility.h"
#include "Task.h"
#include "IsolationLevel.h"

namespace Lupus {
    namespace Data {
        class ITransaction;
        class Command;

        class LUPUS_API Connection : public boost::noncopyable
        {
        public:
            
            virtual ~Connection() = default;

            virtual Task<std::shared_ptr<ITransaction>> BeginTransactionAsync(IsolationLevel) throw(std::invalid_argument);
            virtual Task<void> ConnectAsync(const std::string&) throw(std::invalid_argument);

            virtual std::string ConnectionString() const NOEXCEPT = 0;
            
            virtual std::shared_ptr<ITransaction> BeginTransaction(IsolationLevel = IsolationLevel::Committed) throw(sql_error) = 0;
            virtual void Connect(const std::string&) throw(sql_error) = 0;
            virtual void Close() NOEXCEPT = 0;
            virtual std::shared_ptr<Command> CreateCommand() throw(sql_error) = 0;
            virtual void Open() throw(sql_error) = 0;
        };
    }
}
