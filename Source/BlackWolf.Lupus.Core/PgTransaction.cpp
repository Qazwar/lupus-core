#include "Internal/PgTransaction.h"

#include <postgres/libpq-fe.h>

namespace Lupus {
    namespace Data {
        namespace Postgres {

            PgTransaction::PgTransaction(PGconn* conn, IsolationLevel level)
            {
                PGresult* result = nullptr;
                mPgConn = conn;

                switch (level) {
                    case IsolationLevel::Uncommitted:
                        if (!(result = PQexec(conn, "SET TRANSACTION READ UNCOMMITED"))) {
                            throw sql_error("database is not connected");
                        } else if (PQresultStatus(result) != PGRES_COMMAND_OK) {
                            PQclear(result);
                            throw sql_error("command failed");
                        } else {
                            PQclear(result);
                        }

                        break;

                    case IsolationLevel::Committed:
                        if (!(result = PQexec(conn, "SET TRANSACTION READ COMMITED"))) {
                            throw sql_error("database is not connected");
                        } else if (PQresultStatus(result) != PGRES_COMMAND_OK) {
                            PQclear(result);
                            throw sql_error("command failed");
                        } else {
                            PQclear(result);
                        }

                        break;

                    case IsolationLevel::Repeatable:
                        if (!(result = PQexec(conn, "SET TRANSACTION REPEATABLE READ"))) {
                            throw sql_error("database is not connected");
                        } else if (PQresultStatus(result) != PGRES_COMMAND_OK) {
                            PQclear(result);
                            throw sql_error("command failed");
                        } else {
                            PQclear(result);
                        }

                        break;

                    case IsolationLevel::Serializable:
                        if (!(result = PQexec(conn, "SET TRANSACTION SERIALIZABLE"))) {
                            throw sql_error("database is not connected");
                        } else if (PQresultStatus(result) != PGRES_COMMAND_OK) {
                            PQclear(result);
                            throw sql_error("command failed");
                        } else {
                            PQclear(result);
                        }

                        break;
                }
            }
            
            PgTransaction::~PgTransaction()
            {
            }

            void PgTransaction::Commit()
            {
                PGresult* result = nullptr;

                if (!(result = PQexec(mPgConn, "COMMIT"))) {
                    throw sql_error("database is not connected");
                } else if (PQresultStatus(result) != PGRES_COMMAND_OK) {
                    PQclear(result);
                    throw sql_error("command failed");
                } else {
                    PQclear(result);
                }

            }
            
            void PgTransaction::Rollback()
            {
                PGresult* result = nullptr;

                if (!(result = PQexec(mPgConn, "ROLLBACK"))) {
                    throw sql_error("database is not connected");
                } else if (PQresultStatus(result) != PGRES_COMMAND_OK) {
                    PQclear(result);
                    throw sql_error("command failed");
                } else {
                    PQclear(result);
                }
            }
        }
    }
}
