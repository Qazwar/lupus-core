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
                virtual std::vector<std::unordered_map<String, boost::any>> ExecuteScalar() throw(sql_error) override;
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
