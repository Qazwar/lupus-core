#include "AsymmetricAlgorithm.h"
#include "CryptoRSA.h"
#include <cryptopp/rsa.h>

using namespace std;

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            AsymmetricAlgorithmFactory::AsymmetricAlgorithmFactory()
            {
                using namespace CryptoPP;
                mPrototypes["rsaes-oaep-sha"] = make_shared<CryptoRSA<RSAES<OAEP<SHA>>>>();
                mPrototypes["rsaes-pkcs"] = make_shared<CryptoRSA<RSAES<PKCS1v15>>>();
            }

            AsymmetricAlgorithmFactory& AsymmetricAlgorithmFactory::GetInstance()
            {
                static AsymmetricAlgorithmFactory instance;
                return instance;
            }

            shared_ptr<AsymmetricAlgorithm> AsymmetricAlgorithmFactory::Create(const string& algorithm) const
            {
                auto it = mPrototypes.find(algorithm);

                if (it != end(mPrototypes)) {
                    return dynamic_pointer_cast<AsymmetricAlgorithm>(it->second->Clone());
                }

                return nullptr;
            }
        }
    }
}
