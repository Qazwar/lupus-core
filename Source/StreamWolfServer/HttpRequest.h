#pragma once

#include <boost/noncopyable.hpp>

#include <string>
#include <memory>

namespace StreamWolf {
    namespace Net {
        namespace Sockets {
            class TcpClient;
        }

        namespace Http {
            class HttpRequest : boost::noncopyable
            {
            public:

                HttpRequest(std::shared_ptr<Sockets::TcpClient>);
                virtual ~HttpRequest() = default;

            private:

                std::shared_ptr<Sockets::TcpClient> mClient;
            };
        }
    }
}
