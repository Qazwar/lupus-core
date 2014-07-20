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

                virtual void Text(const std::string&) NOEXCEPT override;
                virtual std::string& Text() NOEXCEPT override;
                virtual const std::string& Text() const NOEXCEPT override;
                virtual std::vector<std::shared_ptr<Parameter>>& Parameters() NOEXCEPT override;
                virtual const std::vector<std::shared_ptr<Parameter>>& Parameters() const NOEXCEPT override;

                virtual std::shared_ptr<Parameter> CreateParameter() NOEXCEPT override;
                virtual int ExecuteNonQuery() throw(sql_error) override;
                virtual std::shared_ptr<IDataReader> ExecuteReader() throw(sql_error) override;
                virtual std::vector<std::unordered_map<std::string, boost::any>> ExecuteScalar() throw(sql_error) override;
                virtual bool Prepare() throw(sql_error) override;

            private:

                pg_result* GetResult() throw(sql_error);

                pg_conn* mPgConn = nullptr;
                bool mPrepared = false;
                std::string mName = "";
                std::string mQuery = "";
                std::vector<std::shared_ptr<Parameter>> mParameters;
            };
        }
    }
}
