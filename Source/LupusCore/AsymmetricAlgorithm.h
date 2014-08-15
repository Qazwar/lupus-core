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
            class LUPUS_API AsymmetricAlgorithm : public IClonable, public boost::noncopyable
            {
            public:

                virtual ~AsymmetricAlgorithm() = default;

				virtual std::vector<uint8_t> Encrypt(const std::vector<uint8_t>& buffer, size_t offset, size_t size) const NOEXCEPT = 0;
				virtual size_t Encrypt(const std::vector<uint8_t>& buffer, size_t offset, size_t size, std::vector<uint8_t>& output, size_t outputOffset) const NOEXCEPT = 0;
				virtual std::vector<uint8_t> Decrypt(std::vector<uint8_t>& buffer, size_t offset, size_t size) const NOEXCEPT = 0;
				virtual size_t Decrypt(const std::vector<uint8_t>& buffer, size_t offset, size_t size, std::vector<uint8_t>& output, size_t outputOffset) const NOEXCEPT = 0;
				virtual const std::vector<uint8_t>& PublicKey() const NOEXCEPT = 0;
				virtual const std::vector<uint8_t>& PrivateKey() const NOEXCEPT = 0;
				virtual void PrivateKey(const std::vector<uint8_t>&) NOEXCEPT = 0;
				virtual void GenerateRandomKey(size_t bitSize) NOEXCEPT = 0;
            };


            class LUPUS_API AsymmetricAlgorithmFactory : public boost::noncopyable
            {
            public:

                static AsymmetricAlgorithmFactory& GetInstance() NOEXCEPT;

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
