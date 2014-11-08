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
#include "IFactory.h"

#include <vector>
#include <memory>
#include <unordered_map>
#include <boost/noncopyable.hpp>

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
            
            class LUPUSCORE_API AsymmetricAlgorithm : public IClonable<AsymmetricAlgorithm>, public boost::noncopyable
            {
            public:

                virtual ~AsymmetricAlgorithm() = default;

                virtual std::vector<uint8_t> Encrypt(const std::vector<uint8_t>& buffer, size_t offset, size_t size) const throw(std::out_of_range) = 0;
                virtual size_t Encrypt(const std::vector<uint8_t>& buffer, size_t offset, size_t size, std::vector<uint8_t>& output, size_t outputOffset) const throw(std::out_of_range) = 0;
                virtual std::vector<uint8_t> Decrypt(std::vector<uint8_t>& buffer, size_t offset, size_t size) const throw(std::out_of_range) = 0;
                virtual size_t Decrypt(const std::vector<uint8_t>& buffer, size_t offset, size_t size, std::vector<uint8_t>& output, size_t outputOffset) const throw(std::out_of_range) = 0;
                virtual std::vector<uint8_t> PublicKey() const NOEXCEPT = 0;
                virtual void PublicKey(const std::vector<uint8_t>&) NOEXCEPT = 0;
                virtual std::vector<uint8_t> PrivateKey() const NOEXCEPT = 0;
                virtual void PrivateKey(const std::vector<uint8_t>&) NOEXCEPT = 0;
                virtual void GenerateRandomKey(unsigned bitSize) NOEXCEPT = 0;
                virtual bool ValidatePrivateKey(KeyValidationLevel level) const NOEXCEPT = 0;
                virtual bool ValidatePublicKey(KeyValidationLevel level) const NOEXCEPT = 0;

                virtual size_t MessageLength(size_t ciphertextLength) const NOEXCEPT = 0;
                virtual size_t CiphertextLength(size_t messageLength) const NOEXCEPT = 0;

                static std::vector<uint8_t> LoadFromFile(const String& path);
                static void SaveToFile(const String& path, const std::vector<uint8_t>& key);
            };


            class LUPUSCORE_API AsymmetricAlgorithmFactory : public IFactory<AsymmetricAlgorithm, String>, public boost::noncopyable
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
                virtual std::shared_ptr<AsymmetricAlgorithm> Create(const String& algorithm) const NOEXCEPT override;

            private:

                AsymmetricAlgorithmFactory();
                virtual ~AsymmetricAlgorithmFactory() = default;

                std::unordered_map<String, std::shared_ptr<AsymmetricAlgorithm>> mPrototypes;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
