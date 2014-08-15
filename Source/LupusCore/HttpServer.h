#pragma once

#include <boost/noncopyable.hpp>

#include <string>
#include <memory>
#include <vector>
#include <thread>
#include <atomic>
#include <exception>
#include <functional>

#include "Utility.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Net {
        namespace Sockets {
            class TcpClient;
            class TcpListener;
        }

        namespace Http {
            class HttpRequest;
            class HttpResponse;

            class LUPUS_API HttpServer : public boost::noncopyable
            {
            public:

                HttpServer(uint16_t port, int backlog);
                virtual ~HttpServer() = default;

                virtual void Start(std::function<void(std::shared_ptr<HttpRequest>, std::shared_ptr<HttpResponse>)>);
                virtual void Stop();

            private:

                void HandleConnection(std::function<void(std::shared_ptr<HttpRequest>, std::shared_ptr<HttpResponse>)>);

                std::atomic<bool> mRun = false;
                std::shared_ptr<Sockets::TcpListener> mListener = nullptr;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
