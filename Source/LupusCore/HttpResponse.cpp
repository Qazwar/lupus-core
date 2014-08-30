#include "HttpResponse.h"
#include "TcpClient.h"

using namespace std;
using namespace Lupus::Net::Sockets;

namespace Lupus {
    namespace Net {
        namespace Http {
            HttpResponse::HttpResponse(shared_ptr<Sockets::TcpClient> client)
            {
                mClient = client;
            }
        }
    }
}
