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

#include "../AsymmetricAlgorithm.h"
#include <cryptopp/osrng.h>
#include <cryptopp/rsa.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            template <typename T>
            class CryptoRSA : public AsymmetricAlgorithm
            {
            public:

                virtual ~CryptoRSA() = default;

                CryptoRSA()
                {
                    CryptoPP::AutoSeededRandomPool rng;

                    mDecryptor.AccessPrivateKey().GenerateRandomWithKeySize(rng, 512);
                    mEncryptor = typename T::Encryptor(mDecryptor.AccessPrivateKey());
                }

                CryptoRSA(const Vector<uint8_t>& buffer)
                {
                    CryptoPP::ByteQueue byteQueue;

                    byteQueue.Put(buffer.data(), buffer.size());
                    mDecryptor.AccessPrivateKey().Load(byteQueue);
                    mEncryptor = typename T::Encryptor(mDecryptor.AccessPrivateKey());
                }

                virtual Pointer<AsymmetricAlgorithm> Clone() const NOEXCEPT override
                {
                    return std::dynamic_pointer_cast<AsymmetricAlgorithm>(MakePointer<CryptoRSA<T>>(PrivateKey()));
                }

                virtual Vector<uint8_t> Encrypt(const Vector<uint8_t>& buffer, size_t offset, size_t size) const throw(OutOfRange) override
                {
                    if (offset > buffer.size()) {
                        throw OutOfRange("offset");
                    } else if (size > buffer.size() - offset) {
                        throw OutOfRange("size");
                    }

                    CryptoPP::AutoSeededRandomPool rng;
                    Vector<uint8_t> result(mEncryptor.CiphertextLength(size));

                    mEncryptor.Encrypt(rng, buffer.data() + offset, size, result.data());
                    return result;
                }

                virtual size_t Encrypt(const Vector<uint8_t>& buffer, size_t offset, size_t size, Vector<uint8_t>& output, size_t outputOffset) const throw(OutOfRange) override
                {
                    size_t length = mEncryptor.CiphertextLength(size);

                    if (offset > buffer.size()) {
                        throw OutOfRange("offset");
                    } else if (size > buffer.size() - offset) {
                        throw OutOfRange("size");
                    } else if (length > output.size() - outputOffset) {
                        throw OutOfRange("transformed bytes exceeding output vector");
                    }

                    CryptoPP::AutoSeededRandomPool rng;

                    mEncryptor.Encrypt(rng, buffer.data() + offset, size, output.data() + outputOffset);
                    return length;
                }

                virtual Vector<uint8_t> Decrypt(Vector<uint8_t>& buffer, size_t offset, size_t size) const throw(OutOfRange) override
                {
                    if (offset > buffer.size()) {
                        throw OutOfRange("offset");
                    } else if (size > buffer.size() - offset) {
                        throw OutOfRange("size");
                    }

                    CryptoPP::AutoSeededRandomPool rng;
                    Vector<uint8_t> result(mDecryptor.MaxPlaintextLength(size));

                    mDecryptor.Decrypt(rng, buffer.data() + offset, size, result.data());
                    return result;
                }

                virtual size_t Decrypt(const Vector<uint8_t>& buffer, size_t offset, size_t size, Vector<uint8_t>& output, size_t outputOffset) const throw(OutOfRange) override
                {
                    size_t length = mDecryptor.MaxPlaintextLength(size);

                    if (offset > buffer.size()) {
                        throw OutOfRange("offset");
                    } else if (size > buffer.size() - offset) {
                        throw OutOfRange("size");
                    } else if (length > output.size() - outputOffset) {
                        throw OutOfRange("transformed bytes exceeding output vector");
                    }

                    CryptoPP::AutoSeededRandomPool rng;

                    mDecryptor.Decrypt(rng, buffer.data() + offset, size, output.data() + outputOffset);
                    return length;
                }

                virtual Vector<uint8_t> PublicKey() const NOEXCEPT override
                {
                    CryptoPP::ByteQueue byteQueue;
                    Vector<uint8_t> buffer;

                    mEncryptor.GetPublicKey().Save(byteQueue);
                    byteQueue.Get(buffer.data(), byteQueue.MaxRetrievable());
                    return buffer;
                }

                virtual void PublicKey(const Vector<uint8_t>& buffer) NOEXCEPT override
                {
                    CryptoPP::ByteQueue byteQueue;
                    byteQueue.Put(buffer.data(), buffer.size());
                    mEncryptor.AccessPublicKey().Load(byteQueue);
                }

                virtual Vector<uint8_t> PrivateKey() const NOEXCEPT override
                {
                    CryptoPP::ByteQueue byteQueue;
                    Vector<uint8_t> buffer;

                    mDecryptor.GetPrivateKey().Save(byteQueue);
                    byteQueue.Get(buffer.data(), byteQueue.MaxRetrievable());
                    return buffer;
                }

                virtual void PrivateKey(const Vector<uint8_t>& buffer) NOEXCEPT override
                {
                    CryptoPP::ByteQueue byteQueue;
                    byteQueue.Put(buffer.data(), buffer.size());
                    mDecryptor.AccessPrivateKey().Load(byteQueue);
                }

                virtual void GenerateRandomKey(unsigned bitSize) NOEXCEPT override
                {
                    CryptoPP::AutoSeededRandomPool rng;

                    mDecryptor.AccessPrivateKey().GenerateRandomWithKeySize(rng, bitSize);
                    mEncryptor = typename T::Encryptor(mDecryptor.AccessPrivateKey());
                }

                virtual bool ValidatePrivateKey(KeyValidationLevel level) const NOEXCEPT override
                {
                    CryptoPP::AutoSeededRandomPool rng;
                    return mDecryptor.GetPrivateKey().Validate(rng, (unsigned)level);
                }

                virtual bool ValidatePublicKey(KeyValidationLevel level) const NOEXCEPT override
                {
                    CryptoPP::AutoSeededRandomPool rng;
                    return mEncryptor.GetPublicKey().Validate(rng, (unsigned)level);
                }

                virtual size_t MessageLength(size_t length) const NOEXCEPT override
                {
                    return mDecryptor.MaxPlaintextLength(length);
                }

                virtual size_t CiphertextLength(size_t length) const NOEXCEPT override
                {
                    return mEncryptor.CiphertextLength(length);
                }

            private:

                typename T::Encryptor mEncryptor;
                typename T::Decryptor mDecryptor;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
