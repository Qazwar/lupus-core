/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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



namespace Lupus {
    namespace Security {
        namespace Cryptography {
            SymmetricAlgorithmFactory::SymmetricAlgorithmFactory()
            {
                mPrototypes["aes"] = MakePointer<CryptoBlockCipher<CryptoPP::AES>>();
                mPrototypes["3des"] = MakePointer<CryptoBlockCipher<CryptoPP::DES_EDE3>>();
                mPrototypes["tripledes"] = MakePointer<CryptoBlockCipher<CryptoPP::DES_EDE3>>();
                mPrototypes["serpent"] = MakePointer<CryptoBlockCipher<CryptoPP::Serpent>>();
                mPrototypes["rc5"] = MakePointer<CryptoBlockCipher<CryptoPP::RC5>>();
                mPrototypes["rc6"] = MakePointer<CryptoBlockCipher<CryptoPP::RC6>>();
                mPrototypes["twofish"] = MakePointer<CryptoBlockCipher<CryptoPP::Twofish>>();
                mPrototypes["blowfish"] = MakePointer<CryptoBlockCipher<CryptoPP::Blowfish>>();
                mPrototypes["idea"] = MakePointer<CryptoBlockCipher<CryptoPP::IDEA>>();
                mPrototypes["camellia"] = MakePointer<CryptoBlockCipher<CryptoPP::Camellia>>();
                mPrototypes["seed"] = MakePointer<CryptoBlockCipher<CryptoPP::SEED>>();
            }

            SymmetricAlgorithmFactory& SymmetricAlgorithmFactory::GetInstance()
            {
                static SymmetricAlgorithmFactory instance;
                return instance;
            }

            Pointer<SymmetricAlgorithm> SymmetricAlgorithmFactory::Create(const String& algorithm) const
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
