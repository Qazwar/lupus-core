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

                virtual std::string KeyExchangeAlgorithm() NOEXCEPT = 0;
                virtual uint32_t KeySize() NOEXCEPT = 0;
                virtual void KeySize(uint32_t) NOEXCEPT = 0;
                virtual uint32_t LegalKeySize() NOEXCEPT = 0;
                virtual std::string SignatureAlgorithm() NOEXCEPT = 0;
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
