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
#pragma once

#include "ICryptoTransform.h"
#include "SymmetricAlgorithm.h"
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            template <typename T>
            class CryptoTransformAlgorithm : public ICryptoTransform, public boost::noncopyable
            {
            public:

                virtual ~CryptoTransformAlgorithm() = default;

                CryptoTransformAlgorithm(const uint8_t* key, size_t size, const uint8_t* iv)
                {
                    mAlgorithm = T(key, size, iv);
                }

                virtual std::vector<uint8_t> TransformFinalBlock(const std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::out_of_range) override
                {
                    if (offset > buffer.size() || size > buffer.size() - offset) {
                        throw std::out_of_range("offset and size does not match buffer size");
                    }

                    std::vector<uint8_t> output(size);
                    CryptoPP::StreamTransformationFilter filter(mAlgorithm, new CryptoPP::ArraySink(output.data(), size));
                    filter.Put(buffer.data() + offset, size);
                    filter.MessageEnd();
                    return std::move(output);
                }

                virtual size_t TransformBlock(const std::vector<uint8_t>& input, size_t inputOffset, size_t inputCount, std::vector<uint8_t>& output, size_t outputOffset) throw(std::out_of_range) override
                {
                    if (inputOffset > input.size() || inputCount > input.size() - inputOffset) {
                        throw std::out_of_range("offset and size does not match buffer size");
                    } else if (inputCount > output.size() - outputOffset) {
                        throw std::out_of_range("transformed bytes exceeding output vector");
                    }

                    CryptoPP::StreamTransformationFilter filter(mAlgorithm, new CryptoPP::ArraySink(output.data() + outputOffset, inputCount));
                    filter.Put(input.data() + inputOffset, inputCount);
                    filter.MessageEnd();
                    return inputCount;
                }

            private:

                T mAlgorithm;
            };

            template <typename T>
            class CryptoBlockCipher : public SymmetricAlgorithm
            {
            public:

                virtual ~CryptoBlockCipher() = default;

                virtual std::shared_ptr<SymmetricAlgorithm> Clone() const NOEXCEPT override
                {
                    return std::dynamic_pointer_cast<SymmetricAlgorithm>(make_shared<CryptoBlockCipher<T>>());
                }

                virtual size_t BlockSize() const NOEXCEPT override
                {
                    return T::BLOCKSIZE;
                }

                virtual size_t MinKeyLength() const NOEXCEPT override
                {
                    return T::MIN_KEYLENGTH;
                }

                virtual size_t MaxKeyLength() const NOEXCEPT override
                {
                    return T::MAX_KEYLENGTH;
                }

                virtual size_t DefaultKeyLength() const NOEXCEPT override
                {
                    return T::DEFAULT_KEYLENGTH;
                }

                virtual size_t IvRequirement() const NOEXCEPT override
                {
                    return T::IV_REQUIREMENT;
                }

                virtual size_t IvLength() const NOEXCEPT override
                {
                    return T::IV_LENGTH;
                }

                virtual CipherMode Mode() const NOEXCEPT override
                {
                    return mMode;
                }

                virtual void Mode(CipherMode mode) NOEXCEPT override
                {
                    mMode = mode;
                }

                virtual const std::vector<uint8_t>& Key() const NOEXCEPT override
                {
                    return mKey;
                }

                virtual void Key(const std::vector<uint8_t>& key) NOEXCEPT override
                {
                    mKey = key;
                }

                virtual const std::vector<uint8_t>& Iv() const NOEXCEPT override
                {
                    return mIv;
                }

                virtual void Iv(const std::vector<uint8_t>& iv) NOEXCEPT override
                {
                    mIv = iv;
                }

                virtual std::shared_ptr<ICryptoTransform> CreateDecryptor() NOEXCEPT override
                {
                    switch (mMode) {
                        case CipherMode::Cbc: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CBC_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Cfb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CFB_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ctr: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CTR_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ecb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::ECB_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ofb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::OFB_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                    }

                    return nullptr;
                }

                virtual std::shared_ptr<ICryptoTransform> CreateDecryptor(CipherMode mode) NOEXCEPT override
                {
                    switch (mode) {
                        case CipherMode::Cbc: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CBC_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Cfb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CFB_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ctr: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CTR_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ecb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::ECB_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ofb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::OFB_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                    }

                    return nullptr;
                }

                virtual std::shared_ptr<ICryptoTransform> CreateDecryptor(CipherMode mode, const std::vector<uint8_t>& key) NOEXCEPT override
                {
                    switch (mode) {
                        case CipherMode::Cbc: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CBC_Mode<T>::Decryption>>(key.data(), key.size(), mIv.data());
                        case CipherMode::Cfb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CFB_Mode<T>::Decryption>>(key.data(), key.size(), mIv.data());
                        case CipherMode::Ctr: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CTR_Mode<T>::Decryption>>(key.data(), key.size(), mIv.data());
                        case CipherMode::Ecb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::ECB_Mode<T>::Decryption>>(key.data(), key.size(), mIv.data());
                        case CipherMode::Ofb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::OFB_Mode<T>::Decryption>>(key.data(), key.size(), mIv.data());
                    }

                    return nullptr;
                }

                virtual std::shared_ptr<ICryptoTransform> CreateDecryptor(CipherMode mode, const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv) NOEXCEPT override
                {
                    switch (mode) {
                        case CipherMode::Cbc: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CBC_Mode<T>::Decryption>>(key.data(), key.size(), iv.data());
                        case CipherMode::Cfb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CFB_Mode<T>::Decryption>>(key.data(), key.size(), iv.data());
                        case CipherMode::Ctr: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CTR_Mode<T>::Decryption>>(key.data(), key.size(), iv.data());
                        case CipherMode::Ecb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::ECB_Mode<T>::Decryption>>(key.data(), key.size(), iv.data());
                        case CipherMode::Ofb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::OFB_Mode<T>::Decryption>>(key.data(), key.size(), iv.data());
                    }

                    return nullptr;
                }

                virtual std::shared_ptr<ICryptoTransform> CreateEncryptor() NOEXCEPT override
                {
                    switch (mMode) {
                        case CipherMode::Cbc: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CBC_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Cfb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CFB_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ctr: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CTR_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ecb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::ECB_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ofb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::OFB_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                    }

                    return nullptr;
                }

                virtual std::shared_ptr<ICryptoTransform> CreateEncryptor(CipherMode mode) NOEXCEPT override
                {
                    switch (mode) {
                        case CipherMode::Cbc: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CBC_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Cfb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CFB_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ctr: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CTR_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ecb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::ECB_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ofb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::OFB_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                    }

                    return nullptr;
                }

                virtual std::shared_ptr<ICryptoTransform> CreateEncryptor(CipherMode mode, const std::vector<uint8_t>& key) NOEXCEPT override
                {
                    switch (mode) {
                        case CipherMode::Cbc: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CBC_Mode<T>::Encryption>>(key.data(), key.size(), mIv.data());
                        case CipherMode::Cfb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CFB_Mode<T>::Encryption>>(key.data(), key.size(), mIv.data());
                        case CipherMode::Ctr: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CTR_Mode<T>::Encryption>>(key.data(), key.size(), mIv.data());
                        case CipherMode::Ecb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::ECB_Mode<T>::Encryption>>(key.data(), key.size(), mIv.data());
                        case CipherMode::Ofb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::OFB_Mode<T>::Encryption>>(key.data(), key.size(), mIv.data());
                    }

                    return nullptr;
                }

                virtual std::shared_ptr<ICryptoTransform> CreateEncryptor(CipherMode mode, const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv) NOEXCEPT override
                {
                    switch (mode) {
                        case CipherMode::Cbc: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CBC_Mode<T>::Encryption>>(key.data(), key.size(), iv.data());
                        case CipherMode::Cfb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CFB_Mode<T>::Encryption>>(key.data(), key.size(), iv.data());
                        case CipherMode::Ctr: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::CTR_Mode<T>::Encryption>>(key.data(), key.size(), iv.data());
                        case CipherMode::Ecb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::ECB_Mode<T>::Encryption>>(key.data(), key.size(), iv.data());
                        case CipherMode::Ofb: return std::make_shared<CryptoTransformAlgorithm<CryptoPP::OFB_Mode<T>::Encryption>>(key.data(), key.size(), iv.data());
                    }

                    return nullptr;
                }

            private:

                CipherMode mMode = CipherMode::Ctr;
                std::vector<uint8_t> mKey;
                std::vector<uint8_t> mIv;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
