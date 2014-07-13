#pragma once

#include <memory>
#include <cstdint>
#include <boost/noncopyable.hpp>

#include "Utility.h"

namespace StreamWolf {
    namespace Net {
        namespace Socket {
            class Socket;

            class NetworkStream : public boost::noncopyable
            {
            public:

                NetworkStream(std::shared_ptr<Socket> socket);

                uint32_t DataAvailable() const throw(socket_error);
                std::shared_ptr<Socket> Handle() const;

            };
        }
    }
}
