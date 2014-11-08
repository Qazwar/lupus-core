/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Lupus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lupus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lupus. If not, see <http://www.gnu.org/licenses/>.
 */
#include "AsymmetricAlgorithm.h"
#include "Internal/CryptoRSA.h"
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
                auto it = mPrototypes.find(algorithm.ToLower());

                if (it != end(mPrototypes)) {
                    return it->second->Clone();
                }

                return nullptr;
            }
        }
    }
}
