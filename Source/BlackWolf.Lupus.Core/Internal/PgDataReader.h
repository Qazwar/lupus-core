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

#include "IDataReader.h"
#include "String.h"

struct pg_result;

namespace Lupus {
    namespace Data {
        namespace Postgres {
            class PgDataReader : public IDataReader
            {
            public:

                PgDataReader(pg_result*);
                virtual ~PgDataReader();

                virtual int Depth() const NOEXCEPT override;
                virtual int FieldCount() const NOEXCEPT override;
                virtual String ColumnName(int) const NOEXCEPT override;
                virtual int ColumnNumber(const String&) const NOEXCEPT override;
                virtual DataType Type(int) const NOEXCEPT override;
                virtual boost::any Value(int) const NOEXCEPT override;
                virtual bool IsNull(int) const NOEXCEPT override;
                virtual bool NextResult() NOEXCEPT override;

            private:

                pg_result* mPgResult;
                int mCurrent = 0;
            };
        }
    }
}
