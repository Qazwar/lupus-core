#pragma once

#include "ICommand.h"

struct pg_conn;
struct pg_result;

namespace StreamWolf {
    namespace Data {
        namespace Postgres {
            class PgCommand : public ICommand
            {
            public:

                PgCommand(pg_conn* conn);
                virtual ~PgCommand();

                virtual void ExecuteNonQueryAsync(std::function<void(ICommand*, int)>) override;
                virtual void ExecuteReaderAsync(std::function<void(ICommand*, std::shared_ptr<IDataReader>)>) override;
                virtual void ExecuteScalarAsync(std::function<void(ICommand*, const std::vector<std::unordered_map<std::string, boost::any>>&)>) override;

                virtual void Text(const std::string&) override;
                virtual std::string& Text() override;
                virtual const std::string& Text() const override;
                virtual std::vector<std::shared_ptr<Parameter>>& Parameters() override;
                virtual const std::vector<std::shared_ptr<Parameter>>& Parameters() const override;

                virtual std::shared_ptr<Parameter> CreateParameter() override;
                virtual int ExecuteNonQuery() override;
                virtual std::shared_ptr<IDataReader> ExecuteReader() override;
                virtual std::vector<std::unordered_map<std::string, boost::any>> ExecuteScalar() override;
                virtual bool Prepare() override;

            private:

                pg_result* GetResult();

                pg_conn* mPgConn = nullptr;
                bool mPrepared = false;
                std::string mName = "";
                std::string mQuery = "";
                std::vector<std::shared_ptr<Parameter>> mParameters;
            };
        }
    }
}
