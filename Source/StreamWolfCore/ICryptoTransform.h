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
                    uint32_t inputOffset,
                    uint32_t inputCount) = 0;
                virtual uint32_t TransformBlock(
                    const std::vector<uint8_t>& input,
                    uint32_t inputOffset,
                    uint32_t inputCount,
                    std::vector<uint8_t>& output,
                    uint32_t outputOffset) = 0;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
