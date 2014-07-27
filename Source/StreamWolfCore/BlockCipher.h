#pragma once

#include "Utility.h"
#include "IClonable.h"
#include "CryptoCipcherEnum.h"

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
            class LUPUS_API BlockCipher : public boost::noncopyable, public IClonable
            {
            public:

                virtual ~BlockCipher() = default;

                virtual uint32_t BlockSize() const NOEXCEPT = 0;
                virtual uint32_t MinKeyLength() const NOEXCEPT = 0;
                virtual uint32_t MaxKeyLength() const NOEXCEPT = 0;
                virtual uint32_t DefaultKeyLength() const NOEXCEPT = 0;
                virtual uint32_t IvRequirement() const NOEXCEPT = 0;
                virtual uint32_t IvLength() const NOEXCEPT = 0;
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

            class LUPUS_API BlockCipherFactory : public boost::noncopyable
            {
                std::unordered_map<std::string, std::shared_ptr<BlockCipher>> mPrototypes;

            public:

                static BlockCipherFactory& GetInstance() NOEXCEPT;

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
                std::shared_ptr<BlockCipher> Create(const std::string& algorithm) const NOEXCEPT;

            private:

                BlockCipherFactory();
                ~BlockCipherFactory() = default;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
