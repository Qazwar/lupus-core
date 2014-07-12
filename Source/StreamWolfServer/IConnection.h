#pragma once

#include <string>
#include <memory>
#include <functional>
#include <boost/noncopyable.hpp>

#include "IsolationLevel.h"

namespace StreamWolf {
    namespace Data {
        class ITransaction;
        class ICommand;

        class IConnection : public boost::noncopyable
        {
        public:
            
            virtual ~IConnection() = default;

            virtual void BeginTransactionAsync(IsolationLevel, std::function<void(IConnection*, std::shared_ptr<ITransaction>)>) = 0;
            virtual void ConnectAsync(const std::string&, std::function<void(IConnection*)>) = 0;

            virtual std::string ConnectionString() const = 0;
            
            virtual std::shared_ptr<ITransaction> BeginTransaction(IsolationLevel = IsolationLevel::Committed) = 0;
            virtual void Connect(const std::string&) = 0;
            virtual void Close() = 0;
            virtual std::shared_ptr<ICommand> CreateCommand() = 0;
            virtual void Open() = 0;
        };
    }
}
