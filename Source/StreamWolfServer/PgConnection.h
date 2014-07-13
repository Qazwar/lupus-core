#pragma once

#include "IConnection.h"

struct pg_conn;

namespace StreamWolf {
    namespace Data {
        namespace Postgres {
            class PgConnection : public IConnection
            {
            public:

                PgConnection() = default;
                PgConnection(const std::string&);

                virtual ~PgConnection();

                virtual void BeginTransactionAsync(IsolationLevel, std::function<void(std::exception_ptr, IConnection*, std::shared_ptr<ITransaction>)>) NOEXCEPT override;
                virtual void ConnectAsync(const std::string&, std::function<void(std::exception_ptr, IConnection*)>) NOEXCEPT override;

                virtual std::string ConnectionString() const NOEXCEPT override;

                virtual std::shared_ptr<ITransaction> BeginTransaction(IsolationLevel = IsolationLevel::Committed) throw(sql_error) override;
                virtual void Connect(const std::string&) throw(sql_error) override;
                virtual void Close() NOEXCEPT override;
                virtual std::shared_ptr<ICommand> CreateCommand() throw(sql_error) override;
                virtual void Open() throw(sql_error) override;

            private:

                pg_conn* mPgConn = nullptr;
                std::string mConnString = "";
            };
        }
    }
}
