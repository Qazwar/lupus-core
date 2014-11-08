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
#include "SymmetricAlgorithm.h"
#include "Internal/CryptoBlockCipher.h"
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

            shared_ptr<SymmetricAlgorithm> SymmetricAlgorithmFactory::Create(const String& algorithm) const
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
