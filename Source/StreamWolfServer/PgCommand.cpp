#include "PgCommand.h"
#include "PgOid.h"
#include "IParameter.h"
#include "Utility.h"

#include <thread>
#include <algorithm>

#include <cstring>

#include <postgres/libpq-fe.h>

using namespace std;

namespace StreamWolf {
    namespace Data {
        namespace Postgres {
            PgCommand::PgCommand(PGconn* conn)
            {
                mPgConn = conn;
            }

            PgCommand::~PgCommand()
            {
            }

            void PgCommand::BeginExecuteNonQuery(function<void(ICommand*, int)> callback)
            {
                thread([this, &callback]() {
                    callback(this, this->ExecuteNonQuery());
                }).detach();
            }
            
            void PgCommand::BeginExecuteReader(function<void(ICommand*, shared_ptr<IDataReader>)> callback)
            {
                thread([this, &callback]() {
                    callback(this, this->ExecuteReader());
                }).detach();
            }
            
            void PgCommand::BeginExecuteScalar(function<void(ICommand*, const vector<unordered_map<string, boost::any>>&)> callback)
            {
                thread([this, &callback]() {
                    callback(this, this->ExecuteScalar());
                }).detach();
            }

            void PgCommand::Text(const string& PgCommand)
            {
                mQuery = PgCommand;
            }

            string& PgCommand::Text()
            {
                return mQuery;
            }

            const string& PgCommand::Text() const
            {
                return mQuery;
            }

            vector<shared_ptr<IParameter>>& PgCommand::Parameters()
            {
                return mParameters;
            }

            const vector<shared_ptr<IParameter>>& PgCommand::Parameters() const
            {
                return mParameters;
            }
            
            void PgCommand::Transaction(shared_ptr<ITransaction> transaction)
            {
                mTransaction = transaction;
            }
            
            shared_ptr<ITransaction> PgCommand::Transaction() const
            {
                return mTransaction;
            }
            
            shared_ptr<IParameter> PgCommand::CreateParameter()
            {
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
            }
            
            vector<unordered_map<string, boost::any>> PgCommand::ExecuteScalar()
            {
                vector<unordered_map<string, boost::any>> scalar;
                PGresult* result = GetResult();
                
                if (!result) {
                    return scalar;
                }

                int rows = PQntuples(result);
                int fields = PQnfields(result);
                scalar.reserve(rows);

                for (int i = 0; i < rows; i++) {
                    unordered_map<string, boost::any> row;

                    for (int j = 0; j < fields; j++) {
                        row[PQfname(result, j)] = (PQgetisnull(result, i, j) == 1) ? nullptr : PQgetvalue(result, i, j);
                    }

                    scalar.push_back(row);
                }

                PQclear(result);
                return scalar;
            }
            
            void PgCommand::Prepare()
            {
                vector<Oid> paramTypes;

                for_each(begin(mParameters), end(mParameters), [&paramTypes](shared_ptr<IParameter>& param) {
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
                        case DataType::Int8: paramTypes.push_back(INT8OID); break;
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

                mName = RandomString<8>().c_str();
                PGresult* result = PQprepare(mPgConn, mName.c_str(), mQuery.c_str(), paramTypes.size(), paramTypes.data());
                mPrepared = (PQresultStatus(result) == PGRES_COMMAND_OK);
                PQclear(result);
            }

            PGresult* PgCommand::GetResult()
            {
                if (!mPrepared) {
                    return PQexec(mPgConn, mQuery.c_str());
                }

                vector<const char*> paramValues;
                vector<int> paramFormats, paramLengths;
                paramValues.reserve(mParameters.size());
                paramFormats.reserve(mParameters.size());
                paramLengths.reserve(mParameters.size());

                for_each(begin(mParameters), end(mParameters), [&paramValues, &paramLengths, &paramFormats](shared_ptr<IParameter>& param) {
                    string value = boost::any_cast<string>(param->Value());
                    paramLengths.push_back(value.length());

                    char* buffer = new char[value.length()];
                    strncpy(buffer, value.c_str(), value.length());
                    paramValues.push_back(buffer);

                    paramFormats.push_back(0); // 0 = string, 1 = binäre
                });

                PGresult* result = PQexecPrepared(mPgConn, mName.c_str(), mParameters.size(), paramValues.data(), paramLengths.data(), paramFormats.data(), 0);

                for_each(begin(paramValues), end(paramValues), [](const char* s) {
                    delete s;
                });
            }
        }
    }
}
