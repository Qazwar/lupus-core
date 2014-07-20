#include "Connection.h"
#include <thread>

using namespace std;

namespace StreamWolf {
    namespace Data {
        void Connection::BeginTransactionAsync(IsolationLevel level, std::function<void(std::exception_ptr, Connection*, std::shared_ptr<ITransaction>)> callback)
        {
            thread([this, level, callback]() {
                try {
                    callback(nullptr, this, this->BeginTransaction(level));
                } catch (...) {
                    callback(current_exception(), this, nullptr);
                }
            }).detach();
        }

        void Connection::ConnectAsync(const string& pgConnectionString, function<void(std::exception_ptr, Connection*)> callback)
        {
            thread([this, pgConnectionString, callback]() {
                try {
                    this->Connect(pgConnectionString);
                    callback(nullptr, this);
                } catch (...) {
                    callback(current_exception(), this);
                }
            }).detach();
        }
    }
}
