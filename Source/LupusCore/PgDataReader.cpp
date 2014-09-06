#include "Private.PgDataReader.h"
#include "Private.PgOid.h"

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
            
            boost::any PgDataReader::Value(int i) const
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
