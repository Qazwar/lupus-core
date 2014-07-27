#pragma once

namespace Lupus {
    namespace Net {
        namespace Security {
            enum class EncryptionPolicy {
                AllowNoEncryption,
                NoEcryption,
                RequireEncryption
            };
        }
    }
}
