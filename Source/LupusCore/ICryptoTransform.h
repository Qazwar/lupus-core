#pragma once

#include "Utility.h"
#include <vector>
#include <cstdint>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            class LUPUS_API ICryptoTransform
            {
            public:

                virtual ~ICryptoTransform() = default;

                virtual std::vector<uint8_t> TransformFinalBlock(
                    const std::vector<uint8_t>& input,
                    size_t inputOffset,
                    size_t inputCount) = 0;
                virtual size_t TransformBlock(
                    const std::vector<uint8_t>& input,
                    size_t inputOffset,
                    size_t inputCount,
                    std::vector<uint8_t>& output,
                    size_t outputOffset) = 0;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
