#include "HttpResponse.h"
#include "TcpClient.h"

using namespace std;
using namespace StreamWolf::Net::Sockets;

namespace StreamWolf {
    namespace Net {
        namespace Http {
            HttpResponse::HttpResponse(shared_ptr<Sockets::TcpClient> client)
            {
                mClient = client;
            }
        }
    }
}
