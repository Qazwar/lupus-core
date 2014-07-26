#pragma once

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            enum class CipherMode {
                Ecb,
                Cbc,
                Cfb,
                Ofb,
                Ctr
            };
        }
    }
}
