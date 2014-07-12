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

                virtual void BeginConnect(const std::string&, std::function<void(IConnection*)>) override;

                virtual std::string ConnectionString() const override;

                virtual std::shared_ptr<ITransaction> BeginTransaction(IsolationLevel = IsolationLevel::Committed) override;
                virtual void Connect(const std::string&) override;
                virtual void ClearPool() override;
                virtual void Close() override;
                virtual std::shared_ptr<ICommand> CreateCommand() override;
                virtual void Open() override;

            private:

                pg_conn* mPgConn = nullptr;
                std::string mConnString = "";
            };
        }
    }
}
