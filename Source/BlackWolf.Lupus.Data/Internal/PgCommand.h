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

#include "../Command.h"

struct pg_conn;
struct pg_result;

namespace Lupus {
    namespace Data {
        namespace Postgres {
            class PgCommand : public Command
            {
            public:

                PgCommand(pg_conn* conn);
                virtual ~PgCommand();

                virtual void Text(const String&) NOEXCEPT override;
                virtual String& Text() NOEXCEPT override;
                virtual const String& Text() const NOEXCEPT override;
                virtual Vector<Pointer<Parameter>>& Parameters() NOEXCEPT override;
                virtual const Vector<Pointer<Parameter>>& Parameters() const NOEXCEPT override;

                virtual Pointer<Parameter> CreateParameter() NOEXCEPT override;
                virtual int ExecuteNonQuery() throw(SqlError) override;
                virtual Pointer<IDataReader> ExecuteReader() throw(SqlError) override;
                virtual Vector<NameCollection<Any>> ExecuteScalar() throw(SqlError) override;
                virtual bool Prepare() throw(SqlError) override;

            private:

                pg_result* GetResult() throw(SqlError);

                pg_conn* mPgConn = nullptr;
                bool mPrepared = false;
                String mName = "";
                String mQuery = "";
                Vector<Pointer<Parameter>> mParameters;
            };
        }
    }
}
