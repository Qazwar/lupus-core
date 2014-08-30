#pragma once

// TODO: Factory f�r Datenbanken einbauen.

#include "Connection.h"

struct pg_conn;

namespace Lupus {
    namespace Data {
        namespace Postgres {
            class PgConnection : public Connection
            {
            public:

                PgConnection() = default;
                PgConnection(const std::string&);

                virtual ~PgConnection();

                virtual std::string ConnectionString() const NOEXCEPT override;

                virtual std::shared_ptr<ITransaction> BeginTransaction(IsolationLevel = IsolationLevel::Committed) throw(sql_error) override;
                virtual void Connect(const std::string&) throw(sql_error) override;
                virtual void Close() NOEXCEPT override;
                virtual std::shared_ptr<Command> CreateCommand() throw(sql_error) override;
                virtual void Open() throw(sql_error) override;

            private:

                pg_conn* mPgConn = nullptr;
                std::string mConnString = "";
            };
        }
    }
}
