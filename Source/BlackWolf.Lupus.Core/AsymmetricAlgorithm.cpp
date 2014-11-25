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
#include "AsymmetricAlgorithm.h"
#include "Internal/CryptoRSA.h"
#include <cryptopp/rsa.h>
#include <cryptopp/files.h>



namespace Lupus {
    namespace Security {
        namespace Cryptography {
            Vector<U8> AsymmetricAlgorithm::LoadFromFile(const String& path)
            {
                CryptoPP::ByteQueue bt;
                CryptoPP::FileSource file(path.ToUTF8().c_str(), true /*pumpAll*/);

                file.TransferTo(bt);
                Vector<U8> buffer((size_t)bt.MaxRetrievable());
                bt.Get(buffer.data(), buffer.size());
                return buffer;
            }

            void AsymmetricAlgorithm::SaveToFile(const String& path, const Vector<U8>& key)
            {
                CryptoPP::ByteQueue bt;
                CryptoPP::FileSink file(path.ToUTF8().c_str());

                bt.Put(key.data(), key.size());
                bt.CopyTo(file);                
            }

            AsymmetricAlgorithmFactory::AsymmetricAlgorithmFactory()
            {
                using namespace CryptoPP;
                mPrototypes["rsaes-oaep-sha"] = MakePointer<CryptoRSA<RSAES<OAEP<SHA>>>>();
                mPrototypes["rsaes-pkcs"] = MakePointer<CryptoRSA<RSAES<PKCS1v15>>>();
            }

            AsymmetricAlgorithmFactory& AsymmetricAlgorithmFactory::GetInstance()
            {
                static AsymmetricAlgorithmFactory instance;
                return instance;
            }

            Pointer<AsymmetricAlgorithm> AsymmetricAlgorithmFactory::Create(const String& algorithm) const
            {
                auto it = mPrototypes.find(algorithm.ToLower());

                if (it != End(mPrototypes)) {
                    return it->second->Clone();
                }

                return nullptr;
            }
        }
    }
}
