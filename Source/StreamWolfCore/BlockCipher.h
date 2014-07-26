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

                virtual std::shared_ptr<class ICryptoTransform> CreateDecryptor() = 0;
                virtual std::shared_ptr<class ICryptoTransform> CreateDecryptor(
                    const std::vector<uint8_t>& key,
                    const std::vector<uint8_t>& iv) throw(std::invalid_argument) = 0;

                virtual std::shared_ptr<class ICryptoTransform> CreateEncryptor() = 0;
                virtual std::shared_ptr<class ICryptoTransform> CreateEncryptor(
                    const std::vector<uint8_t>& key,
                    const std::vector<uint8_t>& iv) throw(std::invalid_argument) = 0;
            };

            class LUPUS_API BlockCipherFactory
            {
                static std::unordered_map<std::string, std::shared_ptr<BlockCipher>> smPrototypes;

            public:

                static std::shared_ptr<BlockCipherFactory> GetInstance() NOEXCEPT;

                /*!
                 * Unterstütze Algorithmen sind:
                 *
                 * \param[in]   algorithm Der zu klonende Algorithmus.
                 *
                 * \returns Zeiger auf den geklonten Algorithmus.
                 */
                std::shared_ptr<BlockCipher> Create(const std::string& algorithm) const NOEXCEPT;

            private:

                BlockCipherFactory();
                ~BlockCipherFactory();
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
