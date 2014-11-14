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
#include "Internal/PgDataReader.h"
#include "Internal/PgOid.h"
#include <postgres/libpq-fe.h>

using namespace std;

namespace Lupus {
    namespace Data {
        namespace Postgres {
            PgDataReader::PgDataReader(PGresult* result)
            {
                mPgResult = result;
            }

            PgDataReader::~PgDataReader()
            {
                PQclear(mPgResult);
            }

            int PgDataReader::Depth() const
            {
                return PQntuples(mPgResult);
            }
            
            int PgDataReader::FieldCount() const
            {
                return PQnfields(mPgResult);
            }
            
            String PgDataReader::ColumnName(int i) const
            {
                return PQfname(mPgResult, i);
            }
            
            int PgDataReader::ColumnNumber(const String& str) const
            {
                return PQfnumber(mPgResult, str.ToUTF8().c_str());
            }
            
            DataType PgDataReader::Type(int i) const
            {
                switch (PQftype(mPgResult, i)) {
                    case BOOLOID: return DataType::Boolean;
                    case BYTEAOID: return DataType::Byte;
                    case CHAROID: return DataType::Character;
                    case VARCHAROID: return DataType::CharacterVarying;
                    case DATEOID: return DataType::Date;
                    case TIMESTAMPOID: return DataType::DateTime;
                    case FLOAT4OID: return DataType::Float;
                    case FLOAT8OID: return DataType::DoublePrecision;
                    case INT2OID: return DataType::SmallInt;
                    case INT4OID: return DataType::Integer;
                    case INT8OID: return DataType::Integer8;
                    case NUMERICOID: return DataType::Numeric;
                    case INTERVALOID: return DataType::Interval;
                    case TEXTOID: return DataType::Text;
                    default: return DataType::Unknown;
                }
            }
            
            Any PgDataReader::Value(int i) const
            {
                return PQgetvalue(mPgResult, mCurrent, i);
            }
            
            bool PgDataReader::IsNull(int i) const
            {
                return (PQgetisnull(mPgResult, mCurrent, i) == 1);
            }
            
            bool PgDataReader::NextResult()
            {
                return (++mCurrent >= PQntuples(mPgResult));
            }
        }
    }
}
