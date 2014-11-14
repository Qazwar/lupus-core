/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
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
