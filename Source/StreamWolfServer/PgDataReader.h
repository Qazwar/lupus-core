#pragma once

#include "IDataReader.h"

struct pg_result;

namespace StreamWolf {
    namespace Data {
        namespace Postgres {
            class PgDataReader : public IDataReader
            {
            public:

                PgDataReader(pg_result*);
                virtual ~PgDataReader();

                virtual int Depth() const override;
                virtual int FieldCount() const override;
                virtual std::string ColumnName(int) const override;
                virtual int ColumnNumber(const std::string&) const override;
                virtual DataType Type(int) const override;
                virtual boost::any Value(int) const override;
                virtual bool IsNull(int) const override;
                virtual bool NextResult() override;

            private:

                pg_result* mPgResult;
                int mCurrent = 0;
            };
        }
    }
}
