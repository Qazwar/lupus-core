#pragma once

#include "AsymmetricAlgorithm.h"
#include <cryptopp/dh.h>
#include <cryptopp/osrng.h>

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            template <typename T>
            class LUPUS_API CryptoKeyExchange : public AsymmetricAlgorithm
            {
            public:

                virtual ~CryptoKeyExchange() = default;
            };
        }
    }
}
