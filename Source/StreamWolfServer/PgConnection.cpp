#include "PgConnection.h"
#include "PgCommand.h"

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

            void PgConnection::ConnectAsync(const string& PgConnectionString, function<void(IConnection*)> callback)
            {
                thread([this, &PgConnectionString, &callback] () {
                    this->Connect(PgConnectionString);
                    callback(this);
                }).detach();
            }
            
            string PgConnection::ConnectionString() const
            {
                return mConnString;
            }

            shared_ptr<ITransaction> PgConnection::BeginTransaction(IsolationLevel level)
            {
                return nullptr;
            }
            
            void PgConnection::Connect(const string& PgConnectionString)
            {
                Close();
                mPgConn = PQconnectdb(PgConnectionString.c_str());
            }
            
            void PgConnection::ClearPool()
            {
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
                Close();
                mPgConn = PQconnectdb(mConnString.c_str());
            }
        }
    }
}
