#pragma once

#include "Command.h"

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
