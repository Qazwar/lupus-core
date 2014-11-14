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
#pragma once

#include "String.h"
#include "IClonable.h"
#include "IFactory.h"
#include "ICryptoTransform.h"

#include <vector>
#include <memory>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    class Stream;

    namespace Security {
        namespace Cryptography {
            class LUPUSCORE_API HashAlgorithm : public ICryptoTransform, public IClonable<HashAlgorithm>
            {
            public:

                virtual ~HashAlgorithm() = default;

                virtual size_t BlockSize() const NOEXCEPT = 0;
                virtual size_t HashSize() const NOEXCEPT = 0;

                virtual std::vector<uint8_t> ComputeHash(const std::vector<uint8_t>&) NOEXCEPT = 0;
                virtual std::vector<uint8_t> ComputeHash(std::shared_ptr<Stream>) = 0;
                virtual std::vector<uint8_t> ComputeHash(const std::vector<uint8_t>& input,
                    size_t inputOffset,
                    size_t inputCount) throw(std::out_of_range) = 0;

                virtual std::vector<uint8_t> TransformFinalBlock(const std::vector<uint8_t>& input, size_t offset, size_t count) throw(std::out_of_range) override;
                virtual size_t TransformBlock(
                    const std::vector<uint8_t>& input,
                    size_t inputOffset,
                    size_t inputCount,
                    std::vector<uint8_t>& output,
                    size_t outputOffset) throw(std::out_of_range) override;
            };

            class LUPUSCORE_API HashAlgorithmFactory : public IFactory<HashAlgorithm, String>, public NonCopyable
            {
            public:
                
                static HashAlgorithmFactory& GetInstance() NOEXCEPT;

                /*!
                 * Unterstützte Algorithmen sind:
                 * - sha1
                 * - sha224
                 * - sha256
                 * - sha384
                 * - sha512
                 * - sha3-224
                 * - sha3-256
                 * - sha3-384
                 * - sha3-512
                 * - tiger
                 * - whirlpool
                 * - ripemd128
                 * - ripemd160
                 * - ripemd256
                 * - ripemd320
                 * - md5
                 *
                 * \param[in]   algorithm Der zu klonende Algorithmus.
                 *
                 * \returns Zeiger auf den geklonten Algorithmus.
                 */
                virtual std::shared_ptr<HashAlgorithm> Create(const String& algorithm) const NOEXCEPT override;

            private:

                HashAlgorithmFactory();
                virtual ~HashAlgorithmFactory() = default;

                NameCollection<std::shared_ptr<HashAlgorithm>> mPrototypes;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
