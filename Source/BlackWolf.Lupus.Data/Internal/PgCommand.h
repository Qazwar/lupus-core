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
                virtual std::vector<std::shared_ptr<Parameter>>& Parameters() NOEXCEPT override;
                virtual const std::vector<std::shared_ptr<Parameter>>& Parameters() const NOEXCEPT override;

                virtual std::shared_ptr<Parameter> CreateParameter() NOEXCEPT override;
                virtual int ExecuteNonQuery() throw(sql_error) override;
                virtual std::shared_ptr<IDataReader> ExecuteReader() throw(sql_error) override;
                virtual std::vector<NameCollection<Any>> ExecuteScalar() throw(sql_error) override;
                virtual bool Prepare() throw(sql_error) override;

            private:

                pg_result* GetResult() throw(sql_error);

                pg_conn* mPgConn = nullptr;
                bool mPrepared = false;
                String mName = "";
                String mQuery = "";
                std::vector<std::shared_ptr<Parameter>> mParameters;
            };
        }
    }
}
