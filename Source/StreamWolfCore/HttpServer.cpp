#include "HttpServer.h"
#include "TcpClient.h"
#include "TcpListener.h"
#include "IPAddress.h"
#include "IPEndPoint.h"
#include "NetworkStream.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

#include <iostream>

using namespace std;
using namespace StreamWolf::Net::Sockets;

namespace StreamWolf {
    namespace Net {
        namespace Http {
            HttpServer::HttpServer(uint16_t port, int32_t backlog)
            {
                try {
                    mListener = make_shared<TcpListener>(IPAddress::Any(), port);
                    mListener->Start(backlog);
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                    rethrow_exception(current_exception());
                }
            }

            void HttpServer::Start(function<void(shared_ptr<HttpRequest>, shared_ptr<HttpResponse>)> callback)
            {
                mRun = true;
                thread(bind(&HttpServer::HandleConnection, this, callback)).detach();
            }

            void HttpServer::Stop()
            {
                mRun.store(false);
            }

            void HttpServer::HandleConnection(function<void(shared_ptr<HttpRequest>, shared_ptr<HttpResponse>)> callback)
            {
                while (mRun.load()) {
                    auto client = mListener->AcceptTcpClient();
                    callback(make_shared<HttpRequest>(client), make_shared<HttpResponse>(client));
                }
            }
        }
    }
}
