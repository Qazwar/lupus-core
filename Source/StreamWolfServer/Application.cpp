#include "Application.h"
#include "HttpServer.h"

#include <cstdio>

using namespace std;
using namespace StreamWolf::Net;
using namespace StreamWolf::Net::Sockets;

namespace StreamWolf {
    namespace Application {
        int Application::Initialize(const vector<string>& args)
        {
            return 0;
        }

        int Application::Execute()
        {
            auto httpServer = make_shared<HttpServer>(8080);
            httpServer->Start();
            getchar();
            httpServer->Stop();
            return 0;
        }

        int Application::Shutdown()
        {
            return 0;
        }
    }
}
