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
#include "HashAlgorithm.h"
#include "Internal/CryptoHash.h"
#include <algorithm>
#include <cctype>
#include <cryptopp/sha.h>
#include <cryptopp/sha3.h>
#include <cryptopp/md5.h>
#include <cryptopp/ripemd.h>
#include <cryptopp/whrlpool.h>
#include <cryptopp/tiger.h>

using namespace std;

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            vector<uint8_t> HashAlgorithm::TransformFinalBlock(const vector<uint8_t>& input, size_t inputOffset, size_t inputCount)
            {
                return std::move(ComputeHash(input, inputOffset, inputCount));
            }

            size_t HashAlgorithm::TransformBlock(const vector<uint8_t>& input, size_t inputOffset, size_t inputCount, vector<uint8_t>& output, size_t outputOffset)
            {
                vector<uint8_t> buffer = ComputeHash(input, inputOffset, inputCount);
                auto iterator = begin(output) + outputOffset;

                if (buffer.size() > output.size() - outputOffset) {
                    throw out_of_range("Transformed bytes exceeding output vector");
                }


                for_each(begin(buffer), end(buffer), [&iterator](const uint8_t& byte) {
                    *(iterator++) = byte;
                });

                return (size_t)buffer.size();
            }

            HashAlgorithmFactory::HashAlgorithmFactory()
            {
                mPrototypes["sha1"] = make_shared<CryptoHash<CryptoPP::SHA1>>();
                mPrototypes["sha224"] = make_shared<CryptoHash<CryptoPP::SHA224>>();
                mPrototypes["sha256"] = make_shared<CryptoHash<CryptoPP::SHA256>>();
                mPrototypes["sha384"] = make_shared<CryptoHash<CryptoPP::SHA384>>();
                mPrototypes["sha512"] = make_shared<CryptoHash<CryptoPP::SHA512>>();
                mPrototypes["sha3-224"] = make_shared<CryptoHash<CryptoPP::SHA3_224>>();
                mPrototypes["sha3-256"] = make_shared<CryptoHash<CryptoPP::SHA3_256>>();
                mPrototypes["sha3-384"] = make_shared<CryptoHash<CryptoPP::SHA3_384>>();
                mPrototypes["sha3-512"] = make_shared<CryptoHash<CryptoPP::SHA3_512>>();
                mPrototypes["tiger"] = make_shared<CryptoHash<CryptoPP::Tiger>>();
                mPrototypes["whirlpool"] = make_shared<CryptoHash<CryptoPP::Whirlpool>>();
                mPrototypes["ripemd128"] = make_shared<CryptoHash<CryptoPP::RIPEMD128>>();
                mPrototypes["ripemd160"] = make_shared<CryptoHash<CryptoPP::RIPEMD160>>();
                mPrototypes["ripemd256"] = make_shared<CryptoHash<CryptoPP::RIPEMD256>>();
                mPrototypes["ripemd320"] = make_shared<CryptoHash<CryptoPP::RIPEMD320>>();
                mPrototypes["md5"] = make_shared<CryptoHash<CryptoPP::Weak::MD5>>();
            }

            HashAlgorithmFactory& HashAlgorithmFactory::GetInstance()
            {
                static HashAlgorithmFactory instance;
                return instance;
            }

            shared_ptr<HashAlgorithm> HashAlgorithmFactory::Create(const String& hash) const
            {
                auto it = mPrototypes.find(hash.ToLower());

                if (it != end(mPrototypes)) {
                    return it->second->Clone();
                }

                return nullptr;
            }
        }
    }
}
