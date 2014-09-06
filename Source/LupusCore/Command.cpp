#include "Command.h"
#include <thread>

using namespace std;

namespace Lupus {
    namespace Data {
        Task<int> Command::ExecuteNonQueryAsync()
        {
            return Task<int>([this]() {
                return this->ExecuteNonQuery();
            });
        }

        Task<shared_ptr<IDataReader>> Command::ExecuteReaderAsync()
        {
            return Task<shared_ptr<IDataReader>>([this]() {
                return this->ExecuteReader();
            });
        }

        Task<vector<unordered_map<String, boost::any>>> Command::ExecuteScalarAsync()
        {
            return Task<vector<unordered_map<String, boost::any>>>([this]() {
                return this->ExecuteScalar();
            });
        }
    }
}
