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
            class HttpResponse : boost::noncopyable
            {
            public:

                HttpResponse(std::shared_ptr<Sockets::TcpClient>);
                virtual ~HttpResponse() = default;

            private:

                std::shared_ptr<Sockets::TcpClient> mClient;
            };
        }
    }
}
