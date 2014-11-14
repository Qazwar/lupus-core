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
