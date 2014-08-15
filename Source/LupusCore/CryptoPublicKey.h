#pragma once

#include "AsymmetricAlgorithm.h"
#include <cryptopp/rsa.h>

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            /*template <typename T>
            class LUPUS_API CryptoPublicKey : public AsymmetricAlgorithm
            {
            public:

				virtual ~CryptoPublicKey() = default;

				virtual std::shared_ptr<CryptoPublicKey>  Clone() NOEXCEPT override
				{
					return std::make_shared<CryptoPublicKey<T>>();
				}
			private:

				T mAlgoritm;
            };*/
        }
    }
}
