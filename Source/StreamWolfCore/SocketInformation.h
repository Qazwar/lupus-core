#pragma once

#include "SocketEnum.h"

#include <vector>
#include <cstdint>

namespace StreamWolf {
    namespace Net {
        namespace Sockets {
            enum class SocketInformationOption {
                None,
                Connected,
                Bound
            };

            extern "C" struct SocketInformation {
                SocketInformationOption Options;
                std::vector<uint8_t> ProtocolInformation;
            };
        }
    }
}
