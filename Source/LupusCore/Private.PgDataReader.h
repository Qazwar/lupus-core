#pragma once

#include "IDataReader.h"

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
                virtual std::string ColumnName(int) const NOEXCEPT override;
                virtual int ColumnNumber(const std::string&) const NOEXCEPT override;
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
