#pragma once

#include "ICryptoTransform.h"
#include "BlockCipher.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            template <typename T>
            class LUPUS_API CryptoBlockCipher : public BlockCipher
            {
            public:
            };

            template <typename T>
            class LUPUS_API CryptoBlockCipherEncryptor : public ICryptoTransform, public IClonable
            {
            public:
            };

            template <typename T>
            class LUPUS_API CryptoBlockCipherDecryptor : public ICryptoTransform, public IClonable
            {
            public:
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
