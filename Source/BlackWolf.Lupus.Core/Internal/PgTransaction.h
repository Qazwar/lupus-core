#pragma once

#include "IsolationLevel.h"
#include "ITransaction.h"

struct pg_conn;

namespace Lupus {
    namespace Data {
        namespace Postgres {
            class PgTransaction : public ITransaction
            {
            public:

                PgTransaction(pg_conn*, IsolationLevel) throw(sql_error);
                virtual ~PgTransaction();

                virtual void Commit() throw(sql_error) override;
                virtual void Rollback() throw(sql_error) override;

            private:

                pg_conn* mPgConn;
            };
        }
    }
}
