/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Lupus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lupus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lupus. If not, see <http://www.gnu.org/licenses/>.
 */
#include "Internal/PgConnection.h"
#include "Internal/PgCommand.h"
#include "Internal/PgTransaction.h"

#include <thread>
#include <postgres/libpq-fe.h>

using namespace std;

namespace Lupus {
    namespace Data {
        namespace Postgres {
            PgConnection::PgConnection(const String& PgConnectionString)
            {
                mPgConn = PQconnectdb(PgConnectionString.ToUTF8().c_str());
            }

            PgConnection::~PgConnection()
            {
                Close();
            }
            
            String PgConnection::ConnectionString() const
            {
                return mConnString;
            }

            shared_ptr<ITransaction> PgConnection::BeginTransaction(IsolationLevel level)
            {
                return make_shared<PgTransaction>(mPgConn, level);
            }
            
            void PgConnection::Connect(const String& pgConnectionString)
            {
                Close();

                if (!(mPgConn = PQconnectdb(pgConnectionString.ToUTF8().c_str()))) {
                    throw sql_error("could not connect to postgres database");
                }
            }
            
            void PgConnection::Close()
            {
                if (mPgConn) {
                    PQfinish(mPgConn);
                    mPgConn = nullptr;
                }
            }
            
            shared_ptr<Command> PgConnection::CreateCommand()
            {
                return make_shared<PgCommand>(mPgConn);
            }
            
            void PgConnection::Open()
            {
                Connect(mConnString);
            }
        }
    }
}
