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

#include <vector>
#include <memory>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            enum class CipherMode {
                Ecb,
                Cbc,
                Cfb,
                Ofb,
                Ctr
            };

            class LUPUSCORE_API SymmetricAlgorithm : public NonCopyable, public IClonable<SymmetricAlgorithm>
            {
            public:

                virtual ~SymmetricAlgorithm() = default;

                virtual U32 BlockSize() const NOEXCEPT = 0;
                virtual U32 MinKeyLength() const NOEXCEPT = 0;
                virtual U32 MaxKeyLength() const NOEXCEPT = 0;
                virtual U32 DefaultKeyLength() const NOEXCEPT = 0;
                virtual U32 IvRequirement() const NOEXCEPT = 0;
                virtual U32 IvLength() const NOEXCEPT = 0;
                virtual CipherMode Mode() const NOEXCEPT = 0;
                virtual void Mode(CipherMode) NOEXCEPT = 0;
                virtual const Vector<U8>& Key() const NOEXCEPT = 0;
                virtual void Key(const Vector<U8>&) NOEXCEPT = 0;
                virtual const Vector<U8>& Iv() const NOEXCEPT = 0;
                virtual void Iv(const Vector<U8>&) NOEXCEPT = 0;

                virtual Pointer<class ICryptoTransform> CreateDecryptor() NOEXCEPT = 0;
                virtual Pointer<class ICryptoTransform> CreateDecryptor(CipherMode) NOEXCEPT = 0;
                virtual Pointer<class ICryptoTransform> CreateDecryptor(CipherMode, const Vector<U8>&) NOEXCEPT = 0;
                virtual Pointer<class ICryptoTransform> CreateDecryptor(
                    CipherMode mode,
                    const Vector<U8>& key,
                    const Vector<U8>& iv) NOEXCEPT = 0;

                virtual Pointer<class ICryptoTransform> CreateEncryptor() NOEXCEPT = 0;
                virtual Pointer<class ICryptoTransform> CreateEncryptor(CipherMode) NOEXCEPT = 0;
                virtual Pointer<class ICryptoTransform> CreateEncryptor(CipherMode, const Vector<U8>&) NOEXCEPT = 0;
                virtual Pointer<class ICryptoTransform> CreateEncryptor(
                    CipherMode mode,
                    const Vector<U8>& key,
                    const Vector<U8>& iv) NOEXCEPT = 0;
            };

            class LUPUSCORE_API SymmetricAlgorithmFactory : public IFactory<SymmetricAlgorithm, String>, public NonCopyable
            {
            public:

                static SymmetricAlgorithmFactory& GetInstance() NOEXCEPT;

                /*!
                 * Unterstütze Algorithmen sind:
                 * - aes
                 * - 3des
                 * - tripledes
                 * - serpent
                 * - rc5
                 * - rc6
                 * - twofish
                 * - blowfish
                 * - idea
                 * - camellia
                 * - seed
                 *
                 * \param[in]   algorithm Der zu klonende Algorithmus.
                 *
                 * \returns Zeiger auf den geklonten Algorithmus.
                 */
                virtual Pointer<SymmetricAlgorithm> Create(const String& algorithm) const NOEXCEPT override;

            private:

                SymmetricAlgorithmFactory();
                virtual ~SymmetricAlgorithmFactory() = default;

                NameCollection<Pointer<SymmetricAlgorithm>> mPrototypes;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
