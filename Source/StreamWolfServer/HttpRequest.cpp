#include "HttpRequest.h"
#include "TcpClient.h"

using namespace std;
using namespace StreamWolf::Net::Sockets;

namespace StreamWolf {
    namespace Net {
        namespace Http {
            Request::Request(shared_ptr<TcpClient> client)
            {
                mClient = client;
            }
        }
    }
}
