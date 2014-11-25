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

                virtual U32 BlockSize() const NOEXCEPT = 0;
                virtual U32 HashSize() const NOEXCEPT = 0;

                virtual Vector<U8> ComputeHash(const Vector<U8>&) NOEXCEPT = 0;
                virtual Vector<U8> ComputeHash(Pointer<Stream>) = 0;
                virtual Vector<U8> ComputeHash(const Vector<U8>& input,
                    U32 inputOffset,
                    U32 inputCount) throw(OutOfRange) = 0;

                virtual Vector<U8> TransformFinalBlock(const Vector<U8>& input, U32 offset, U32 count) throw(OutOfRange) override;
                virtual U32 TransformBlock(
                    const Vector<U8>& input,
                    U32 inputOffset,
                    U32 inputCount,
                    Vector<U8>& output,
                    U32 outputOffset) throw(OutOfRange) override;
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
                virtual Pointer<HashAlgorithm> Create(const String& algorithm) const NOEXCEPT override;

            private:

                HashAlgorithmFactory();
                virtual ~HashAlgorithmFactory() = default;

                NameCollection<Pointer<HashAlgorithm>> mPrototypes;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
