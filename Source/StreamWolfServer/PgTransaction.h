#pragma once

#include "IsolationLevel.h"
#include "ITransaction.h"

struct pg_conn;

namespace StreamWolf {
    namespace Data {
        namespace Postgres {
            class PgTransaction : public ITransaction
            {
            public:

                PgTransaction(pg_conn*, IsolationLevel);
                virtual ~PgTransaction();

                virtual void Commit() override;
                virtual void Rollback() override;

            private:

                pg_conn* mPgConn;
            };
        }
    }
}
