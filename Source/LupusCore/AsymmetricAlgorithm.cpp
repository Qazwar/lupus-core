#include "AsymmetricAlgorithm.h"
#include "Private.CryptoRSA.h"
#include <cryptopp/rsa.h>
#include <cryptopp/files.h>

using namespace std;

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            vector<uint8_t> AsymmetricAlgorithm::LoadFromFile(const String& path)
            {
                CryptoPP::ByteQueue bt;
                CryptoPP::FileSource file(path.ToUTF8().c_str(), true /*pumpAll*/);

                file.TransferTo(bt);
                vector<uint8_t> buffer(bt.MaxRetrievable());
                bt.Get(buffer.data(), buffer.size());
                return buffer;
            }

            void AsymmetricAlgorithm::SaveToFile(const String& path, const vector<uint8_t>& key)
            {
                CryptoPP::ByteQueue bt;
                CryptoPP::FileSink file(path.ToUTF8().c_str());

                bt.Put(key.data(), key.size());
                bt.CopyTo(file);                
            }

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

            shared_ptr<AsymmetricAlgorithm> AsymmetricAlgorithmFactory::Create(const String& algorithm) const
            {
                auto it = mPrototypes.find(algorithm);

                if (it != end(mPrototypes)) {
                    return it->second->Clone();
                }

                return nullptr;
            }
        }
    }
}
