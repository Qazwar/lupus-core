#include "HttpRequest.h"
#include "TcpClient.h"

using namespace std;
using namespace Lupus::Net::Sockets;

namespace Lupus {
    namespace Net {
        namespace Http {
            HttpRequest::HttpRequest(shared_ptr<TcpClient> client)
            {
                mClient = client;
            }
        }
    }
}
