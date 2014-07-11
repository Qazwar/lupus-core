#include "PgConnection.h"

#include <thread>
#include <postgres/libpq-fe.h>

using namespace std;

namespace StreamWolf {
    namespace Data {
        namespace Postgres {
            Connection::Connection(const string& connectionString)
            {
                mPgConn = PQconnectdb(connectionString.c_str());
            }

            Connection::~Connection()
            {
                Close();
            }

            void Connection::BeginConnect(const string& connectionString, function<void(IConnection*)> callback)
            {
                thread([this, &connectionString, &callback] () {
                    this->Connect(connectionString);
                    callback(this);
                }).detach();
            }
            
            string Connection::ConnectionString() const
            {
                return mConnString;
            }

            shared_ptr<ITransaction> Connection::BeginTransaction(IsolationLevel level = IsolationLevel::Committed)
            {
            }
            
            void Connection::Connect(const string& connectionString)
            {
                Close();
                mPgConn = PQconnectdb(connectionString.c_str());
            }
            
            void Connection::ClearPool()
            {
            }
            
            void Connection::Close()
            {
                if (mPgConn) {
                    PQfinish(mPgConn);
                    mPgConn = nullptr;
                }
            }
            
            shared_ptr<ICommand> Connection::CreateCommand()
            {
            }
            
            void Connection::Open()
            {
            }
        }
    }
}
