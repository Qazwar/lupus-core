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
            enum class KeyValidationLevel {
                BasicCheck = 0,
                FunctionalityCheck,
                WeaknessCheck,
                SecurityCheck
            };
            
            class LUPUSCORE_API AsymmetricAlgorithm : public IClonable<AsymmetricAlgorithm>, public NonCopyable
            {
            public:

                virtual ~AsymmetricAlgorithm() = default;

                virtual Vector<U8> Encrypt(const Vector<U8>& buffer, U32 offset, U32 size) const throw(OutOfRange) = 0;
                virtual U32 Encrypt(const Vector<U8>& buffer, U32 offset, U32 size, Vector<U8>& output, U32 outputOffset) const throw(OutOfRange) = 0;
                virtual Vector<U8> Decrypt(Vector<U8>& buffer, U32 offset, U32 size) const throw(OutOfRange) = 0;
                virtual U32 Decrypt(const Vector<U8>& buffer, U32 offset, U32 size, Vector<U8>& output, U32 outputOffset) const throw(OutOfRange) = 0;
                virtual Vector<U8> PublicKey() const NOEXCEPT = 0;
                virtual void PublicKey(const Vector<U8>&) NOEXCEPT = 0;
                virtual Vector<U8> PrivateKey() const NOEXCEPT = 0;
                virtual void PrivateKey(const Vector<U8>&) NOEXCEPT = 0;
                virtual void GenerateRandomKey(unsigned bitSize) NOEXCEPT = 0;
                virtual bool ValidatePrivateKey(KeyValidationLevel level) const NOEXCEPT = 0;
                virtual bool ValidatePublicKey(KeyValidationLevel level) const NOEXCEPT = 0;

                virtual U32 MessageLength(U32 ciphertextLength) const NOEXCEPT = 0;
                virtual U32 CiphertextLength(U32 messageLength) const NOEXCEPT = 0;

                static Vector<U8> LoadFromFile(const String& path);
                static void SaveToFile(const String& path, const Vector<U8>& key);
            };


            class LUPUSCORE_API AsymmetricAlgorithmFactory : public IFactory<AsymmetricAlgorithm, String>, public NonCopyable
            {
            public:

                static AsymmetricAlgorithmFactory& GetInstance() NOEXCEPT;

                /*!
                 * Unterstütze Algorithmen sind:
                 * - rsaes-oaep-sha
                 * - rsaes-pkcs
                 *
                 * \param[in]   algorithm Der zu klonende Algorithmus.
                 *
                 * \returns Zeiger auf den geklonten Algorithmus.
                 */
                virtual Pointer<AsymmetricAlgorithm> Create(const String& algorithm) const NOEXCEPT override;

            private:

                AsymmetricAlgorithmFactory();
                virtual ~AsymmetricAlgorithmFactory() = default;

                NameCollection<Pointer<AsymmetricAlgorithm>> mPrototypes;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
