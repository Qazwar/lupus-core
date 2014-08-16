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
            enum class CipherMode {
                Ecb,
                Cbc,
                Cfb,
                Ofb,
                Ctr
            };

            class LUPUS_API SymmetricAlgorithm : public boost::noncopyable, public IClonable
            {
            public:

                virtual ~SymmetricAlgorithm() = default;

                virtual size_t BlockSize() const NOEXCEPT = 0;
                virtual size_t MinKeyLength() const NOEXCEPT = 0;
                virtual size_t MaxKeyLength() const NOEXCEPT = 0;
                virtual size_t DefaultKeyLength() const NOEXCEPT = 0;
                virtual size_t IvRequirement() const NOEXCEPT = 0;
                virtual size_t IvLength() const NOEXCEPT = 0;
                virtual CipherMode Mode() const NOEXCEPT = 0;
                virtual void Mode(CipherMode) NOEXCEPT = 0;
                virtual const std::vector<uint8_t>& Key() const NOEXCEPT = 0;
                virtual void Key(const std::vector<uint8_t>&) NOEXCEPT = 0;
                virtual const std::vector<uint8_t>& Iv() const NOEXCEPT = 0;
                virtual void Iv(const std::vector<uint8_t>&) NOEXCEPT = 0;

                virtual std::shared_ptr<class ICryptoTransform> CreateDecryptor() NOEXCEPT = 0;
                virtual std::shared_ptr<class ICryptoTransform> CreateDecryptor(CipherMode) NOEXCEPT = 0;
                virtual std::shared_ptr<class ICryptoTransform> CreateDecryptor(CipherMode, const std::vector<uint8_t>&) NOEXCEPT = 0;
                virtual std::shared_ptr<class ICryptoTransform> CreateDecryptor(
                    CipherMode mode,
                    const std::vector<uint8_t>& key,
                    const std::vector<uint8_t>& iv) NOEXCEPT = 0;

                virtual std::shared_ptr<class ICryptoTransform> CreateEncryptor() NOEXCEPT = 0;
                virtual std::shared_ptr<class ICryptoTransform> CreateEncryptor(CipherMode) NOEXCEPT = 0;
                virtual std::shared_ptr<class ICryptoTransform> CreateEncryptor(CipherMode, const std::vector<uint8_t>&) NOEXCEPT = 0;
                virtual std::shared_ptr<class ICryptoTransform> CreateEncryptor(
                    CipherMode mode,
                    const std::vector<uint8_t>& key,
                    const std::vector<uint8_t>& iv) NOEXCEPT = 0;
            };

            class LUPUS_API SymmetricAlgorithmFactory : public boost::noncopyable
            {
            public:

                static SymmetricAlgorithmFactory& GetInstance() NOEXCEPT;

                /*!
                 * Unterstütze Algorithmen sind:
                 * - aes
                 * - 3des
                 * - tripledes
                 * - serpent
                 * - rc5
                 * - rc6
                 * - twofish
                 * - blowfish
                 * - idea
                 * - camellia
                 * - seed
                 *
                 * \param[in]   algorithm Der zu klonende Algorithmus.
                 *
                 * \returns Zeiger auf den geklonten Algorithmus.
                 */
                std::shared_ptr<SymmetricAlgorithm> Create(const std::string& algorithm) const NOEXCEPT;

            private:

                SymmetricAlgorithmFactory();
                virtual ~SymmetricAlgorithmFactory() = default;

                std::unordered_map<std::string, std::shared_ptr<SymmetricAlgorithm>> mPrototypes;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
