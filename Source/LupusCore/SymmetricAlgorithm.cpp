#include "SymmetricAlgorithm.h"
#include "CryptoBlockCipher.h"
#include <cryptopp/aes.h>
#include <cryptopp/des.h>
#include <cryptopp/serpent.h>
#include <cryptopp/rc5.h>
#include <cryptopp/rc6.h>
#include <cryptopp/twofish.h>
#include <cryptopp/blowfish.h>
#include <cryptopp/idea.h>
#include <cryptopp/camellia.h>
#include <cryptopp/seed.h>
#include <cryptopp/panama.h>
#include <cryptopp/sosemanuk.h>
#include <cryptopp/salsa.h>
#include <cryptopp/modes.h>

using namespace std;

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            SymmetricAlgorithmFactory::SymmetricAlgorithmFactory()
            {
                mPrototypes["aes"] = make_shared<CryptoBlockCipher<CryptoPP::AES>>();
                mPrototypes["3des"] = make_shared<CryptoBlockCipher<CryptoPP::DES_EDE3>>();
                mPrototypes["tripledes"] = make_shared<CryptoBlockCipher<CryptoPP::DES_EDE3>>();
                mPrototypes["serpent"] = make_shared<CryptoBlockCipher<CryptoPP::Serpent>>();
                mPrototypes["rc5"] = make_shared<CryptoBlockCipher<CryptoPP::RC5>>();
                mPrototypes["rc6"] = make_shared<CryptoBlockCipher<CryptoPP::RC6>>();
                mPrototypes["twofish"] = make_shared<CryptoBlockCipher<CryptoPP::Twofish>>();
                mPrototypes["blowfish"] = make_shared<CryptoBlockCipher<CryptoPP::Blowfish>>();
                mPrototypes["idea"] = make_shared<CryptoBlockCipher<CryptoPP::IDEA>>();
                mPrototypes["camellia"] = make_shared<CryptoBlockCipher<CryptoPP::Camellia>>();
                mPrototypes["seed"] = make_shared<CryptoBlockCipher<CryptoPP::SEED>>();
            }

            SymmetricAlgorithmFactory& SymmetricAlgorithmFactory::GetInstance()
            {
                static SymmetricAlgorithmFactory instance;
                return instance;
            }

            shared_ptr<SymmetricAlgorithm> SymmetricAlgorithmFactory::Create(const string& algorithm) const
            {
                auto it = mPrototypes.find(algorithm);

                if (it != end(mPrototypes)) {
                    return dynamic_pointer_cast<SymmetricAlgorithm>(it->second->Clone());
                }

                return nullptr;
            }
        }
    }
}
