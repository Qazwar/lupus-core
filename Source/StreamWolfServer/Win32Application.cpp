#ifdef _MSC_VER
#include <cstdio>
#include <cstring>
#include <iostream>
#include <boost/program_options.hpp>

#include "../LupusCore/HttpRequest.h"
#include "../LupusCore/HttpResponse.h"
#include "../LupusCore/HttpServer.h"
#include "../LupusCore/Socket.h"
#include "../LupusCore/Integer.h"
#include "Application.h"

#include <Windows.h> // Muss als letztes eingebunden werden

using namespace std;
using namespace Lupus;
using namespace Lupus::Net;
using namespace Lupus::Net::Http;
using namespace Lupus::Net::Sockets;
namespace po = boost::program_options;

namespace StreamWolf {
    namespace Application {
        int Application::Initialize(int argc, char** argv)
        {
            WSADATA wsaData;

            memset(&wsaData, 0, sizeof(WSADATA));

            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
                return WSAGetLastError();
            }

            po::variables_map vm;
            po::options_description desc("Allowed options");
            desc.add_options()
                ("help", "produce help message")
                ("port", po::value<uint16_t>(&mPort), "set port to listen")
                ("backlog", po::value<uint32_t>(&mBacklog), "set backlog queue length");
            po::store(po::parse_command_line(argc, argv, desc), vm);

            mHttp = vm.count("http") > 0 || vm.count("http only") > 0;

            if (vm.count("help")) {
                cout << desc << endl;
            }

            return 0;
        }

        int Application::Execute()
        {
            auto httpServer = make_shared<HttpServer>(mPort, mBacklog);
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
#endif
