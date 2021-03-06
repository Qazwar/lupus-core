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
#pragma once

// TODO: Factory für Datenbanken einbauen.

#include "../Connection.h"

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
