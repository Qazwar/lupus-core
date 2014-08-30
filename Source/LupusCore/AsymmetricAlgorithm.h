#pragma once

#include "Utility.h"
#include "IClonable.h"

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

            class LUPUS_API AsymmetricAlgorithm : public IClonable, public boost::noncopyable
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

                static std::vector<uint8_t> LoadFromFile(const std::string& path);
                static void SaveToFile(const std::string& path, const std::vector<uint8_t>& key);
            };


            class LUPUS_API AsymmetricAlgorithmFactory : public boost::noncopyable
            {
            public:

                static AsymmetricAlgorithmFactory& GetInstance() NOEXCEPT;

                /*!
                 * Unterst�tze Algorithmen sind:
                 * - rsaes-oaep-sha
                 * - rsaes-pkcs
                 *
                 * \param[in]   algorithm Der zu klonende Algorithmus.
                 *
                 * \returns Zeiger auf den geklonten Algorithmus.
                 */
                std::shared_ptr<AsymmetricAlgorithm> Create(const std::string& algorithm) const NOEXCEPT;

            private:

                AsymmetricAlgorithmFactory();
                virtual ~AsymmetricAlgorithmFactory() = default;

                std::unordered_map<std::string, std::shared_ptr<AsymmetricAlgorithm>> mPrototypes;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
