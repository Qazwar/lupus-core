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
#include "Internal/PgCommand.h"
#include "Internal/PgOid.h"
#include "Internal/PgDataReader.h"
#include "Parameter.h"
#include "Utility.h"

#include <thread>
#include <algorithm>

#include <cstring>

#include <postgres/libpq-fe.h>

using namespace std;

namespace Lupus {
    namespace Data {
        namespace Postgres {
            PgCommand::PgCommand(PGconn* conn)
            {
                mPgConn = conn;
            }

            PgCommand::~PgCommand()
            {
            }

            void PgCommand::Text(const String& PgCommand)
            {
                mQuery = PgCommand;
            }

            String& PgCommand::Text()
            {
                return mQuery;
            }

            const String& PgCommand::Text() const
            {
                return mQuery;
            }

            vector<shared_ptr<Parameter>>& PgCommand::Parameters()
            {
                return mParameters;
            }

            const vector<shared_ptr<Parameter>>& PgCommand::Parameters() const
            {
                return mParameters;
            }
            
            shared_ptr<Parameter> PgCommand::CreateParameter()
            {
                shared_ptr<Parameter> param = make_shared<Parameter>();
                mParameters.push_back(param);
                return param;
            }
            
            int PgCommand::ExecuteNonQuery()
            {
                PGresult* result = GetResult();
                int rows = PQntuples(result);
                PQclear(result);
                return rows;
            }
            
            shared_ptr<IDataReader> PgCommand::ExecuteReader()
            {
                return make_shared<PgDataReader>(GetResult());
            }
            
            vector<NameCollection<Any>> PgCommand::ExecuteScalar()
            {
                vector<NameCollection<Any>> scalar;
                PGresult* result = GetResult();
                
                if (!result) {
                    return scalar;
                }

                int rows = PQntuples(result);
                int fields = PQnfields(result);
                scalar.reserve(rows);

                for (int i = 0; i < rows; i++) {
                    NameCollection<Any> row;

                    for (int j = 0; j < fields; j++) {
                        row[PQfname(result, j)] = (PQgetisnull(result, i, j) == 1) ? "" : PQgetvalue(result, i, j);
                    }

                    scalar.push_back(row);
                }

                PQclear(result);
                return scalar;
            }
            
            bool PgCommand::Prepare()
            {
                vector<Oid> paramTypes;

                for_each(begin(mParameters), end(mParameters), [&paramTypes](shared_ptr<Parameter>& param) {
                    switch (param->DbType()) {
                        case DataType::Boolean: paramTypes.push_back(BOOLOID); break;
                        case DataType::Byte: paramTypes.push_back(BYTEAOID); break;
                        case DataType::Character: paramTypes.push_back(CHAROID); break;
                        case DataType::CharacterVarying: paramTypes.push_back(VARCHAROID); break;
                        case DataType::Date: paramTypes.push_back(DATEOID); break;
                        case DataType::DateTime: paramTypes.push_back(TIMESTAMPOID); break;
                        case DataType::Decimal: paramTypes.push_back(NUMERICOID); break;
                        case DataType::DoublePrecision: paramTypes.push_back(FLOAT8OID); break;
                        case DataType::Float: paramTypes.push_back(FLOAT4OID); break;
                        case DataType::Integer: paramTypes.push_back(INT4OID); break;
                        case DataType::Integer8: paramTypes.push_back(INT8OID); break;
                        case DataType::Interval: paramTypes.push_back(INTERVALOID); break;
                        case DataType::Numeric: paramTypes.push_back(NUMERICOID); break;
                        case DataType::Real: paramTypes.push_back(FLOAT4OID); break;
                        case DataType::Serial: paramTypes.push_back(INT4OID); break;
                        case DataType::Serial8: paramTypes.push_back(INT8OID); break;
                        case DataType::SmallFloat: paramTypes.push_back(FLOAT4OID); break;
                        case DataType::SmallInt: paramTypes.push_back(INT2OID); break;
                        case DataType::Text: paramTypes.push_back(TEXTOID); break;
                        default: paramTypes.push_back(UNKNOWNOID); break;
                    }
                });

                mName = RandomString(8);
                PGresult* result = PQprepare(mPgConn, mName.ToUTF8().c_str(), mQuery.ToUTF8().c_str(), (int)paramTypes.size(), paramTypes.data());

                if (!result) {
                    throw sql_error("database is not connected");
                }

                mPrepared = (PQresultStatus(result) == PGRES_COMMAND_OK);
                PQclear(result);
                return mPrepared;
            }

            PGresult* PgCommand::GetResult()
            {
                PGresult* result = nullptr;

                if (!mPrepared) {
                    if (!(result = PQexec(mPgConn, mQuery.ToUTF8().c_str()))) {
                        throw sql_error("database is not connected");
                    } else if (PQresultStatus(result) != PGRES_COMMAND_OK) {
                        throw sql_error("error while executing command");
                    } else {
                        return result;
                    }
                }

                vector<const char*> paramValues;
                vector<int> paramFormats, paramLengths;
                paramValues.reserve(mParameters.size());
                paramFormats.reserve(mParameters.size());
                paramLengths.reserve(mParameters.size());

                for_each(begin(mParameters), end(mParameters), [&paramValues, &paramLengths, &paramFormats](shared_ptr<Parameter>& param) {
                    String value = boost::any_cast<String>(param->Value());
                    paramLengths.push_back((int)value.Length());

                    if (value.IsEmpty()) {
                        char* buffer = new char[value.Length()];
                        strncpy_s(buffer, value.Length(), value.ToUTF8().c_str(), value.Length());
                        paramValues.push_back(buffer);
                    } else {
                        paramValues.push_back("");
                    }

                    paramFormats.push_back(0); // 0 = String, 1 = binär
                });

                result = PQexecPrepared(mPgConn, mName.ToUTF8().c_str(), (int)mParameters.size(), paramValues.data(), paramLengths.data(), paramFormats.data(), 0);

                for_each(begin(paramValues), end(paramValues), [](const char* s) {
                    delete s;
                });

                if (!result) {
                    throw sql_error("database is not connected");
                } else if (PQresultStatus(result) != PGRES_COMMAND_OK) {
                    throw sql_error("error while executing command");
                }

                return result;
            }
        }
    }
}
