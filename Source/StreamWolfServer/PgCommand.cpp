#include "PgCommand.h"

#include <thread>
#include <postgres/libpq-fe.h>

using namespace std;

namespace StreamWolf {
    namespace Data {
        namespace Postgres {
            Command::Command(PGconn* conn)
            {
                mPgConn = conn;
            }

            Command::~Command()
            {
            }

            void Command::BeginExecuteNonQuery(function<void(ICommand*, int)> callback)
            {
                thread([this, &callback]() {
                    callback(this, this->ExecuteNonQuery());
                }).detach();
            }
            
            void Command::BeginExecuteReader(function<void(ICommand*, shared_ptr<IDataReader>)> callback)
            {
                thread([this, &callback]() {
                    callback(this, this->ExecuteReader());
                }).detach();
            }
            
            void Command::BeginExecuteScalar(function<void(ICommand*, vector<unordered_map<string, boost::any>>&)> callback)
            {
                thread([this, &callback]() {
                    callback(this, this->ExecuteScalar());
                }).detach();
            }

            void Command::Text(const string&)
            {
            }
            
            string& Command::Text() const
            {
            }
            
            unordered_map<string, shared_ptr<IParameter>>& Command::Parameters() const
            {
            }
            
            void Command::Transaction(shared_ptr<ITransaction> transaction)
            {
                mTransaction = transaction;
            }
            
            shared_ptr<ITransaction> Command::Transaction() const
            {
                return mTransaction;
            }
            
            shared_ptr<IParameter> Command::CreateParameter()
            {
            }
            
            int Command::ExecuteNonQuery()
            {
            }
            
            shared_ptr<IDataReader> Command::ExecuteReader()
            {
            }
            
            vector<unordered_map<string, boost::any>> Command::ExecuteScalar()
            {
            }
            
            void Command::Prepare()
            {
            }
        }
    }
}
