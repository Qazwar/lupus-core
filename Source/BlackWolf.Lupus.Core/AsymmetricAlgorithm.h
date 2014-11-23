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

                virtual Vector<uint8_t> Encrypt(const Vector<uint8_t>& buffer, size_t offset, size_t size) const throw(OutOfRange) = 0;
                virtual size_t Encrypt(const Vector<uint8_t>& buffer, size_t offset, size_t size, Vector<uint8_t>& output, size_t outputOffset) const throw(OutOfRange) = 0;
                virtual Vector<uint8_t> Decrypt(Vector<uint8_t>& buffer, size_t offset, size_t size) const throw(OutOfRange) = 0;
                virtual size_t Decrypt(const Vector<uint8_t>& buffer, size_t offset, size_t size, Vector<uint8_t>& output, size_t outputOffset) const throw(OutOfRange) = 0;
                virtual Vector<uint8_t> PublicKey() const NOEXCEPT = 0;
                virtual void PublicKey(const Vector<uint8_t>&) NOEXCEPT = 0;
                virtual Vector<uint8_t> PrivateKey() const NOEXCEPT = 0;
                virtual void PrivateKey(const Vector<uint8_t>&) NOEXCEPT = 0;
                virtual void GenerateRandomKey(unsigned bitSize) NOEXCEPT = 0;
                virtual bool ValidatePrivateKey(KeyValidationLevel level) const NOEXCEPT = 0;
                virtual bool ValidatePublicKey(KeyValidationLevel level) const NOEXCEPT = 0;

                virtual size_t MessageLength(size_t ciphertextLength) const NOEXCEPT = 0;
                virtual size_t CiphertextLength(size_t messageLength) const NOEXCEPT = 0;

                static Vector<uint8_t> LoadFromFile(const String& path);
                static void SaveToFile(const String& path, const Vector<uint8_t>& key);
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
