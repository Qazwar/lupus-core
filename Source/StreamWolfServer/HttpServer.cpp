#include "HttpServer.h"
#include "TcpClient.h"
#include "TcpListener.h"
#include "IPAddress.h"
#include "IPEndPoint.h"
#include "NetworkStream.h"

#include <iostream>

using namespace std;
using namespace StreamWolf::Net::Sockets;

namespace StreamWolf {
    namespace Net {
        HttpServer::HttpServer(uint16_t port)
        {
            try {
                mListener = make_shared<TcpListener>(IPAddress::Any, port);
                mListener->Start(100);
            } catch (const exception& e) {
                cout << e.what() << endl;
                rethrow_exception(current_exception());
            }
        }

        void HttpServer::Start()
        {
            mRun = true;

            thread([this](shared_ptr<TcpListener> listener, std::atomic<bool>& run) {
                while (run.load()) {
                    try {
                        this->HandleClient(listener->AcceptTcpClient());
                    } catch (const exception& e) {
                        cout << e.what() << endl;
                    }
                }
            }, mListener, std::ref(mRun)).detach();
        }
        
        void HttpServer::Stop()
        {
            mRun.store(false);
        }

        void HttpServer::HandleClient(shared_ptr<TcpClient> client)
        {
            thread([=]() {
                vector<uint8_t> buffer(client->Available());
                auto stream = client->GetStream();
                int32_t n = stream->Read(buffer, 0, buffer.size());

                if (n < 0) {
                    int err = WSAGetLastError();
                    cout << GetLastSocketErrorString() << endl;
                } else if (n == 0) {
                    cout << "No connection" << endl;
                } else {
                    cout << buffer.data() << endl;
                }
                // TODO: Anfrage bearbeiten
            }).detach();
        }
    }
}
