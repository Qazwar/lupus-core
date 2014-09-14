#include "HttpListenerRequest.h"
#include "Encoding.h"
#include "Version.h"
#include "Uri.h"
#include "IPEndPoint.h"
#include "Stream.h"

using namespace std;
using namespace Lupus::Net::Sockets;

namespace Lupus {
    namespace Net {
        HttpListenerRequest::HttpListenerRequest(shared_ptr<Lupus::InputStream> stream, shared_ptr<IPEndPoint> local, shared_ptr<IPEndPoint> remote) :
            mStream(stream), mLocalEP(local), mRemoteEP(remote)
        {
            // TODO: Http parsen und in Felder einfügen.
        }
    }
}
