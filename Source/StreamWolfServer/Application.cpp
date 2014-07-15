#include "Application.h"
#include "HttpServer.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "Socket.h"

#include <Windows.h>

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
using namespace StreamWolf::Net;
using namespace StreamWolf::Net::Http;
using namespace StreamWolf::Net::Sockets;

namespace StreamWolf {
    namespace Application {
        int Application::Initialize(const vector<string>& args)
        {
            WSADATA wsaData;

            memset(&wsaData, 0, sizeof(WSADATA));

            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
                cerr << GetLastSocketErrorString() << endl;
            }

            return 0;
        }

        int Application::Execute()
        {
            auto httpServer = make_shared<HttpServer>(8080);
            httpServer->Start([](shared_ptr<HttpRequest> request, shared_ptr<HttpResponse> response) {
                cout << "Connected" << endl;
            });
            getchar();
            httpServer->Stop();
            return 0;
        }

        int Application::Shutdown()
        {
            WSACleanup();
            return 0;
        }
    }
}
