#include "Command.h"
#include <thread>

using namespace std;

namespace Lupus {
    namespace Data {
        void Command::ExecuteNonQueryAsync(function<void(exception_ptr, Command*, int)> callback)
        {
            thread([this, callback]() {
                try {
                    callback(nullptr, this, this->ExecuteNonQuery());
                } catch (...) {
                    callback(current_exception(), this, -1);
                }
            }).detach();
        }

        void Command::ExecuteReaderAsync(function<void(exception_ptr, Command*, shared_ptr<IDataReader>)> callback)
        {
            thread([this, callback]() {
                try {
                    callback(nullptr, this, this->ExecuteReader());
                } catch (...) {
                    callback(current_exception(), this, nullptr);
                }
            }).detach();
        }

        void Command::ExecuteScalarAsync(function<void(exception_ptr, Command*, const vector<unordered_map<string, boost::any>>&)> callback)
        {
            thread([this, callback]() {
                try {
                    callback(nullptr, this, this->ExecuteScalar());
                } catch (...) {
                    callback(current_exception(), this, vector<unordered_map<string, boost::any>>());
                }
            }).detach();
        }
    }
}
