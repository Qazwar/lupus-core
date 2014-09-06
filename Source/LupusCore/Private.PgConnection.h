#pragma once

// TODO: Factory für Datenbanken einbauen.

#include "Connection.h"

struct pg_conn;

namespace Lupus {
    namespace Data {
        namespace Postgres {
            class PgConnection : public Connection
            {
            public:

                PgConnection() = default;
                PgConnection(const String&);

                virtual ~PgConnection();

                virtual String ConnectionString() const NOEXCEPT override;

                virtual std::shared_ptr<ITransaction> BeginTransaction(IsolationLevel = IsolationLevel::Committed) throw(sql_error) override;
                virtual void Connect(const String&) throw(sql_error) override;
                virtual void Close() NOEXCEPT override;
                virtual std::shared_ptr<Command> CreateCommand() throw(sql_error) override;
                virtual void Open() throw(sql_error) override;

            private:

                pg_conn* mPgConn = nullptr;
                String mConnString = "";
            };
        }
    }
}
