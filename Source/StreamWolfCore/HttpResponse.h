#pragma once

#include <boost/noncopyable.hpp>

#include <string>
#include <memory>

#include "Utility.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Net {
        namespace Sockets {
            class TcpClient;
        }

        namespace Http {
            class SWC_API HttpResponse : boost::noncopyable
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

#ifdef _MSC_VER
#pragma warning(pop)
#endif
