#pragma once

#include "Utility.h"
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
            class LUPUS_API HashAlgorithm : public ICryptoTransform, public IClonable
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

            class LUPUS_API HashAlgorithmFactory : public boost::noncopyable
            {
            public:
                
                static HashAlgorithmFactory& GetInstance() NOEXCEPT;

                /*!
                 * Unterstütze Algorithmen sind:
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
                std::shared_ptr<HashAlgorithm> Create(const std::string& algorithm) const NOEXCEPT;

            private:

                HashAlgorithmFactory();
                virtual ~HashAlgorithmFactory() = default;

                std::unordered_map<std::string, std::shared_ptr<HashAlgorithm>> mPrototypes;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
