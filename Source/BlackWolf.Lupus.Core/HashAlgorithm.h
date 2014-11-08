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

#include "String.h"
#include "IClonable.h"
#include "ICryptoTransform.h"

#include <vector>
#include <memory>
#include <unordered_map>
#include <boost/noncopyable.hpp>

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

            class LUPUSCORE_API HashAlgorithmFactory : public boost::noncopyable
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
                std::shared_ptr<HashAlgorithm> Create(const String& algorithm) const NOEXCEPT;

            private:

                HashAlgorithmFactory();
                virtual ~HashAlgorithmFactory() = default;

                std::unordered_map<String, std::shared_ptr<HashAlgorithm>> mPrototypes;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
