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
            
            shared_ptr<Command> PgConnection::CreateCommand()
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
