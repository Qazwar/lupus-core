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

                CryptoTransformAlgorithm(const U8* key, U32 size, const U8* iv)
                {
                    mAlgorithm = T(key, size, iv);
                }

                virtual Vector<U8> TransformFinalBlock(const Vector<U8>& buffer, U32 offset, U32 size) throw(OutOfRange) override
                {
                    if (offset > buffer.size()) {
                        throw OutOfRange("offset");
                    } else if (size > buffer.size() - offset) {
                        throw OutOfRange("size");
                    }

                    Vector<U8> output(size);
                    CryptoPP::StreamTransformationFilter filter(mAlgorithm, new CryptoPP::ArraySink(output.data(), size));
                    filter.Put(buffer.data() + offset, size);
                    filter.MessageEnd();
                    return std::move(output);
                }

                virtual U32 TransformBlock(const Vector<U8>& input, U32 inputOffset, U32 inputCount, Vector<U8>& output, U32 outputOffset) throw(OutOfRange) override
                {
                    if (inputOffset > input.size()) {
                        throw OutOfRange("inputOffset");
                    } else if (inputCount > input.size() - inputOffset) {
                        throw OutOfRange("inputCount");
                    } else if (inputCount > output.size() - outputOffset) {
                        throw OutOfRange("inputCount");
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

                virtual Pointer<SymmetricAlgorithm> Clone() const NOEXCEPT override
                {
                    return std::dynamic_pointer_cast<SymmetricAlgorithm>(MakePointer<CryptoBlockCipher<T>>());
                }

                virtual U32 BlockSize() const NOEXCEPT override
                {
                    return T::BLOCKSIZE;
                }

                virtual U32 MinKeyLength() const NOEXCEPT override
                {
                    return T::MIN_KEYLENGTH;
                }

                virtual U32 MaxKeyLength() const NOEXCEPT override
                {
                    return T::MAX_KEYLENGTH;
                }

                virtual U32 DefaultKeyLength() const NOEXCEPT override
                {
                    return T::DEFAULT_KEYLENGTH;
                }

                virtual U32 IvRequirement() const NOEXCEPT override
                {
                    return T::IV_REQUIREMENT;
                }

                virtual U32 IvLength() const NOEXCEPT override
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

                virtual const Vector<U8>& Key() const NOEXCEPT override
                {
                    return mKey;
                }

                virtual void Key(const Vector<U8>& key) NOEXCEPT override
                {
                    mKey = key;
                }

                virtual const Vector<U8>& Iv() const NOEXCEPT override
                {
                    return mIv;
                }

                virtual void Iv(const Vector<U8>& iv) NOEXCEPT override
                {
                    mIv = iv;
                }

                virtual Pointer<ICryptoTransform> CreateDecryptor() NOEXCEPT override
                {
                    switch (mMode) {
                        case CipherMode::Cbc: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CBC_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Cfb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CFB_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ctr: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CTR_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ecb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::ECB_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ofb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::OFB_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                    }

                    return nullptr;
                }

                virtual Pointer<ICryptoTransform> CreateDecryptor(CipherMode mode) NOEXCEPT override
                {
                    switch (mode) {
                        case CipherMode::Cbc: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CBC_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Cfb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CFB_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ctr: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CTR_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ecb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::ECB_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ofb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::OFB_Mode<T>::Decryption>>(mKey.data(), mKey.size(), mIv.data());
                    }

                    return nullptr;
                }

                virtual Pointer<ICryptoTransform> CreateDecryptor(CipherMode mode, const Vector<U8>& key) NOEXCEPT override
                {
                    switch (mode) {
                        case CipherMode::Cbc: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CBC_Mode<T>::Decryption>>(key.data(), key.size(), mIv.data());
                        case CipherMode::Cfb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CFB_Mode<T>::Decryption>>(key.data(), key.size(), mIv.data());
                        case CipherMode::Ctr: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CTR_Mode<T>::Decryption>>(key.data(), key.size(), mIv.data());
                        case CipherMode::Ecb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::ECB_Mode<T>::Decryption>>(key.data(), key.size(), mIv.data());
                        case CipherMode::Ofb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::OFB_Mode<T>::Decryption>>(key.data(), key.size(), mIv.data());
                    }

                    return nullptr;
                }

                virtual Pointer<ICryptoTransform> CreateDecryptor(CipherMode mode, const Vector<U8>& key, const Vector<U8>& iv) NOEXCEPT override
                {
                    switch (mode) {
                        case CipherMode::Cbc: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CBC_Mode<T>::Decryption>>(key.data(), key.size(), iv.data());
                        case CipherMode::Cfb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CFB_Mode<T>::Decryption>>(key.data(), key.size(), iv.data());
                        case CipherMode::Ctr: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CTR_Mode<T>::Decryption>>(key.data(), key.size(), iv.data());
                        case CipherMode::Ecb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::ECB_Mode<T>::Decryption>>(key.data(), key.size(), iv.data());
                        case CipherMode::Ofb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::OFB_Mode<T>::Decryption>>(key.data(), key.size(), iv.data());
                    }

                    return nullptr;
                }

                virtual Pointer<ICryptoTransform> CreateEncryptor() NOEXCEPT override
                {
                    switch (mMode) {
                        case CipherMode::Cbc: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CBC_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Cfb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CFB_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ctr: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CTR_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ecb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::ECB_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ofb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::OFB_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                    }

                    return nullptr;
                }

                virtual Pointer<ICryptoTransform> CreateEncryptor(CipherMode mode) NOEXCEPT override
                {
                    switch (mode) {
                        case CipherMode::Cbc: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CBC_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Cfb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CFB_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ctr: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CTR_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ecb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::ECB_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                        case CipherMode::Ofb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::OFB_Mode<T>::Encryption>>(mKey.data(), mKey.size(), mIv.data());
                    }

                    return nullptr;
                }

                virtual Pointer<ICryptoTransform> CreateEncryptor(CipherMode mode, const Vector<U8>& key) NOEXCEPT override
                {
                    switch (mode) {
                        case CipherMode::Cbc: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CBC_Mode<T>::Encryption>>(key.data(), key.size(), mIv.data());
                        case CipherMode::Cfb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CFB_Mode<T>::Encryption>>(key.data(), key.size(), mIv.data());
                        case CipherMode::Ctr: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CTR_Mode<T>::Encryption>>(key.data(), key.size(), mIv.data());
                        case CipherMode::Ecb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::ECB_Mode<T>::Encryption>>(key.data(), key.size(), mIv.data());
                        case CipherMode::Ofb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::OFB_Mode<T>::Encryption>>(key.data(), key.size(), mIv.data());
                    }

                    return nullptr;
                }

                virtual Pointer<ICryptoTransform> CreateEncryptor(CipherMode mode, const Vector<U8>& key, const Vector<U8>& iv) NOEXCEPT override
                {
                    switch (mode) {
                        case CipherMode::Cbc: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CBC_Mode<T>::Encryption>>(key.data(), key.size(), iv.data());
                        case CipherMode::Cfb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CFB_Mode<T>::Encryption>>(key.data(), key.size(), iv.data());
                        case CipherMode::Ctr: return MakePointer<CryptoTransformAlgorithm<CryptoPP::CTR_Mode<T>::Encryption>>(key.data(), key.size(), iv.data());
                        case CipherMode::Ecb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::ECB_Mode<T>::Encryption>>(key.data(), key.size(), iv.data());
                        case CipherMode::Ofb: return MakePointer<CryptoTransformAlgorithm<CryptoPP::OFB_Mode<T>::Encryption>>(key.data(), key.size(), iv.data());
                    }

                    return nullptr;
                }

            private:

                CipherMode mMode = CipherMode::Ctr;
                Vector<U8> mKey;
                Vector<U8> mIv;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
