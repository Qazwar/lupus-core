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

#include "../ICryptoTransform.h"
#include "../SymmetricAlgorithm.h"
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
            class CryptoTransformAlgorithm : public ICryptoTransform, public NonCopyable
            {
            public:

                virtual ~CryptoTransformAlgorithm() = default;

                CryptoTransformAlgorithm(const uint8_t* key, size_t size, const uint8_t* iv)
                {
                    mAlgorithm = T(key, size, iv);
                }

                virtual std::vector<uint8_t> TransformFinalBlock(const std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::out_of_range) override
                {
                    if (offset > buffer.size()) {
                        throw std::out_of_range("offset");
                    } else if (size > buffer.size() - offset) {
                        throw std::out_of_range("size");
                    }

                    std::vector<uint8_t> output(size);
                    CryptoPP::StreamTransformationFilter filter(mAlgorithm, new CryptoPP::ArraySink(output.data(), size));
                    filter.Put(buffer.data() + offset, size);
                    filter.MessageEnd();
                    return std::move(output);
                }

                virtual size_t TransformBlock(const std::vector<uint8_t>& input, size_t inputOffset, size_t inputCount, std::vector<uint8_t>& output, size_t outputOffset) throw(std::out_of_range) override
                {
                    if (inputOffset > input.size()) {
                        throw std::out_of_range("inputOffset");
                    } else if (inputCount > input.size() - inputOffset) {
                        throw std::out_of_range("inputCount");
                    } else if (inputCount > output.size() - outputOffset) {
                        throw std::out_of_range("inputCount");
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
