#pragma once

#include <string>
#include <memory>
#include <functional>
#include <boost/noncopyable.hpp>

#include "Utility.h"
#include "IsolationLevel.h"

namespace Lupus {
    namespace Data {
        class ITransaction;
        class Command;

        class SWC_API Connection : public boost::noncopyable
        {
        public:
            
            virtual ~Connection() = default;

            virtual void BeginTransactionAsync(IsolationLevel, std::function<void(std::exception_ptr, Connection*, std::shared_ptr<ITransaction>)>) NOEXCEPT;
            virtual void ConnectAsync(const std::string&, std::function<void(std::exception_ptr, Connection*)>) NOEXCEPT;

            virtual std::string ConnectionString() const NOEXCEPT = 0;
            
            virtual std::shared_ptr<ITransaction> BeginTransaction(IsolationLevel = IsolationLevel::Committed) throw(sql_error) = 0;
            virtual void Connect(const std::string&) throw(sql_error) = 0;
            virtual void Close() NOEXCEPT = 0;
            virtual std::shared_ptr<Command> CreateCommand() throw(sql_error) = 0;
            virtual void Open() throw(sql_error) = 0;
        };
    }
}
