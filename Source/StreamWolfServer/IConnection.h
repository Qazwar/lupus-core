#pragma once

#include <string>
#include <memory>
#include <functional>
#include <boost/noncopyable.hpp>

#include "Utility.h"
#include "IsolationLevel.h"

namespace StreamWolf {
    namespace Data {
        class ITransaction;
        class ICommand;

        class IConnection : public boost::noncopyable
        {
        public:
            
            virtual ~IConnection() = default;

            virtual void BeginTransactionAsync(IsolationLevel, std::function<void(IConnection*, std::shared_ptr<ITransaction>)>) NOEXCEPT = 0;
            virtual void ConnectAsync(const std::string&, std::function<void(IConnection*)>) NOEXCEPT = 0;

            virtual std::string ConnectionString() const NOEXCEPT = 0;
            
            virtual std::shared_ptr<ITransaction> BeginTransaction(IsolationLevel = IsolationLevel::Committed) throw(sql_error) = 0;
            virtual void Connect(const std::string&) throw(sql_error) = 0;
            virtual void Close() NOEXCEPT = 0;
            virtual std::shared_ptr<ICommand> CreateCommand() throw(sql_error) = 0;
            virtual void Open() throw(sql_error) = 0;
        };
    }
}
