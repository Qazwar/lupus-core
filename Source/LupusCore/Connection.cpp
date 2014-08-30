#include "Connection.h"
#include <thread>

using namespace std;

namespace Lupus {
    namespace Data {
        Task<shared_ptr<ITransaction>> Connection::BeginTransactionAsync(IsolationLevel level)
        {
            return Task<shared_ptr<ITransaction>>([this, level]() {
                return this->BeginTransaction(level);
            });
        }

        Task<void> Connection::ConnectAsync(const string& connectionString)
        {
            return Task<void>([this, &connectionString]() {
                this->Connect(connectionString);
            });
        }
    }
}
