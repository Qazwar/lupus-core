#pragma once

#include <boost/noncopyable.hpp>

#include <string>
#include <memory>
#include <vector>
#include <thread>
#include <atomic>
#include <exception>

namespace StreamWolf {
    namespace Net {
        namespace Sockets {
            class TcpClient;
            class TcpListener;
        }

        class HttpServer : public boost::noncopyable
        {
        public:

            HttpServer(uint16_t port);
            virtual ~HttpServer() = default;

            virtual void Start();
            virtual void Stop();

            virtual void HandleClient(std::shared_ptr<Sockets::TcpClient>);

        private:

            std::atomic<bool> mRun = false;
            std::shared_ptr<Sockets::TcpListener> mListener = nullptr;
        };
    }
}
