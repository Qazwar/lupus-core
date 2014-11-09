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
