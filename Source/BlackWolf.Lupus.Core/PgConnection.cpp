#include "Internal/PgConnection.h"
#include "Internal/PgCommand.h"
#include "Internal/PgTransaction.h"

#include <thread>
#include <postgres/libpq-fe.h>

using namespace std;

namespace Lupus {
    namespace Data {
        namespace Postgres {
            PgConnection::PgConnection(const String& PgConnectionString)
            {
                mPgConn = PQconnectdb(PgConnectionString.ToUTF8().c_str());
            }

            PgConnection::~PgConnection()
            {
                Close();
            }
            
            String PgConnection::ConnectionString() const
            {
                return mConnString;
            }

            shared_ptr<ITransaction> PgConnection::BeginTransaction(IsolationLevel level)
            {
                return make_shared<PgTransaction>(mPgConn, level);
            }
            
            void PgConnection::Connect(const String& pgConnectionString)
            {
                Close();

                if (!(mPgConn = PQconnectdb(pgConnectionString.ToUTF8().c_str()))) {
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
