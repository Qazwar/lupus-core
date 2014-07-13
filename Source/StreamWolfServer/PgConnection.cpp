#include "PgConnection.h"
#include "PgCommand.h"
#include "PgTransaction.h"

#include <thread>
#include <postgres/libpq-fe.h>

using namespace std;

namespace StreamWolf {
    namespace Data {
        namespace Postgres {
            PgConnection::PgConnection(const string& PgConnectionString)
            {
                mPgConn = PQconnectdb(PgConnectionString.c_str());
            }

            PgConnection::~PgConnection()
            {
                Close();
            }

            void PgConnection::BeginTransactionAsync(IsolationLevel level, std::function<void(std::exception_ptr, std::shared_ptr<ITransaction>)> callback)
            {
                thread([this, level, callback]() {
                    try {
                        callback(nullptr, this->BeginTransaction(level));
                    } catch (...) {
                        callback(current_exception(), nullptr);
                    }
                }).detach();
            }

            void PgConnection::ConnectAsync(const string& pgConnectionString, function<void(std::exception_ptr, IConnection*)> callback)
            {
                thread([this, pgConnectionString, callback] () {
                    try {
                        this->Connect(pgConnectionString);
                        callback(nullptr, this);
                    } catch (...) {
                        callback(current_exception(), nullptr);
                    }
                }).detach();
            }
            
            string PgConnection::ConnectionString() const
            {
                return mConnString;
            }

            shared_ptr<ITransaction> PgConnection::BeginTransaction(IsolationLevel level)
            {
                return make_shared<PgTransaction>(mPgConn, level);
            }
            
            void PgConnection::Connect(const string& pgConnectionString)
            {
                Close();

                if (!(mPgConn = PQconnectdb(pgConnectionString.c_str()))) {
                    throw sql_error("could not connect to postgres database");
                }
            }
            
            void PgConnection::Close()
            {
                if (mPgConn) {
                    PQfinish(mPgConn);
                    mPgConn = nullptr;
                }
            }
            
            shared_ptr<ICommand> PgConnection::CreateCommand()
            {
                return make_shared<PgCommand>(mPgConn);
            }
            
            void PgConnection::Open()
            {
                Connect(mConnString);
            }
        }
    }
}
