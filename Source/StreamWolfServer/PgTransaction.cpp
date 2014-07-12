#include "PgTransaction.h"

#include <postgres/libpq-fe.h>

namespace StreamWolf {
    namespace Data {
        namespace Postgres {

            PgTransaction::PgTransaction(PGconn* conn, IsolationLevel level)
            {
                mPgConn = conn;

                switch (level) {
                    case IsolationLevel::Uncommitted:
                        PQclear(PQexec(conn, "SET TRANSACTION READ UNCOMMITED"));
                        break;

                    case IsolationLevel::Committed:
                        PQclear(PQexec(conn, "SET TRANSACTION READ COMMITED"));
                        break;

                    case IsolationLevel::Repeatable:
                        PQclear(PQexec(conn, "SET TRANSACTION REPEATABLE READ"));
                        break;

                    case IsolationLevel::Serializable:
                        PQclear(PQexec(conn, "SET TRANSACTION SERIALIZABLE"));
                        break;
                }
            }
            
            PgTransaction::~PgTransaction()
            {
            }

            void PgTransaction::Commit()
            {
                PQclear(PQexec(mPgConn, "COMMIT"));
            }
            
            void PgTransaction::Rollback()
            {
                PQclear(PQexec(mPgConn, "ROLLBACK"));
            }
        }
    }
}
