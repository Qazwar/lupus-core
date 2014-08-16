#pragma once

#include "AsymmetricAlgorithm.h"
#include <cryptopp/osrng.h>
#include <cryptopp/rsa.h>

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            template <typename T>
            class LUPUS_API CryptoRSA : public AsymmetricAlgorithm
            {
            public:

                virtual ~CryptoRSA() = default;

                CryptoRSA()
                {
                    CryptoPP::AutoSeededRandomPool rng;

                    mDecryptor.AccessPrivateKey().GenerateRandomWithKeySize(rng, 512);
                    mEncryptor = typename T::Encryptor(mDecryptor.AccessPrivateKey());
                }

                CryptoRSA(const std::vector<uint8_t>& buffer)
                {
                    CryptoPP::ByteQueue byteQueue;

                    byteQueue.Put(buffer.data(), buffer.size());
                    mDecryptor.AccessPrivateKey().Load(byteQueue);
                    mEncryptor = typename T::Encryptor(mDecryptor.AccessPrivateKey());
                }

                virtual std::shared_ptr<IClonable> Clone() const NOEXCEPT override
                {
                    return std::make_shared<CryptoRSA<T>>(PrivateKey());
                }

                virtual std::vector<uint8_t> Encrypt(const std::vector<uint8_t>& buffer, size_t offset, size_t size) const throw(std::out_of_range) override
                {
                    if (offset > buffer.size() || size > buffer.size() - offset) {
                        throw std::out_of_range("offset and size does not match buffer size");
                    }

                    CryptoPP::AutoSeededRandomPool rng;
                    std::vector<uint8_t> result(mEncryptor.CiphertextLength(size));

                    mEncryptor.Encrypt(rng, buffer.data() + offset, size, &result[0]);
                    return result;
                }

                virtual size_t Encrypt(const std::vector<uint8_t>& buffer, size_t offset, size_t size, std::vector<uint8_t>& output, size_t outputOffset) const throw(std::out_of_range) override
                {
                    size_t length = mEncryptor.CiphertextLength(size);

                    if (offset > buffer.size() || size > buffer.size() - offset) {
                        throw std::out_of_range("offset and size does not match buffer size");
                    } else if (length > output.size() - outputOffset) {
                        throw std::out_of_range("transformed bytes exceeding output vector");
                    }

                    CryptoPP::AutoSeededRandomPool rng;

                    mEncryptor.Encrypt(rng, buffer.data() + offset, size, &output[0] + outputOffset);
                    return length;
                }

                virtual std::vector<uint8_t> Decrypt(std::vector<uint8_t>& buffer, size_t offset, size_t size) const throw(std::out_of_range) override
                {
                    if (offset > buffer.size() || size > buffer.size() - offset) {
                        throw std::out_of_range("offset and size does not match buffer size");
                    }

                    CryptoPP::AutoSeededRandomPool rng;
                    std::vector<uint8_t> result(mDecryptor.MaxPlaintextLength(size));

                    mDecryptor.Decrypt(rng, buffer.data() + offset, size, &result[0]);
                    return result;
                }

                virtual size_t Decrypt(const std::vector<uint8_t>& buffer, size_t offset, size_t size, std::vector<uint8_t>& output, size_t outputOffset) const throw(std::out_of_range) override
                {
                    size_t length = mDecryptor.MaxPlaintextLength(size);

                    if (offset > buffer.size() || size > buffer.size() - offset) {
                        throw std::out_of_range("offset and size does not match buffer size");
                    } else if (length > output.size() - outputOffset) {
                        throw std::out_of_range("transformed bytes exceeding output vector");
                    }

                    CryptoPP::AutoSeededRandomPool rng;

                    mDecryptor.Decrypt(rng, buffer.data() + offset, size, &output[0] + outputOffset);
                    return length;
                }

                virtual std::vector<uint8_t> PublicKey() const NOEXCEPT override
                {
                    CryptoPP::ByteQueue byteQueue;
                    std::vector<uint8_t> buffer;

                    mEncryptor.GetPublicKey().Save(byteQueue);
                    byteQueue.Get(&buffer[0], byteQueue.MaxRetrievable());
                    return buffer;
                }

                virtual void PublicKey(const std::vector<uint8_t>& buffer) NOEXCEPT override
                {
                    CryptoPP::ByteQueue byteQueue;
                    byteQueue.Put(buffer.data(), buffer.size());
                    mEncryptor.AccessPublicKey().Load(byteQueue);
                }

                virtual std::vector<uint8_t> PrivateKey() const NOEXCEPT override
                {
                    CryptoPP::ByteQueue byteQueue;
                    std::vector<uint8_t> buffer;

                    mDecryptor.GetPrivateKey().Save(byteQueue);
                    byteQueue.Get(&buffer[0], byteQueue.MaxRetrievable());
                    return buffer;
                }

                virtual void PrivateKey(const std::vector<uint8_t>& buffer) NOEXCEPT override
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

            private:

                typename T::Encryptor mEncryptor;
                typename T::Decryptor mDecryptor;
            };
        }
    }
}