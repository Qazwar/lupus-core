#pragma once

#include <boost/noncopyable.hpp>
#include <vector>
#include <cstdint>
#include "Utility.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            namespace X509Certificates {
                // TODO: Zertifikat implementieren

                class LUPUS_API X509Certificate : public boost::noncopyable
                {
                public:

                    X509Certificate();
                    X509Certificate(const std::vector<uint8_t>& buffer);
                    X509Certificate(const std::string& fileName);
                    X509Certificate(std::shared_ptr<X509Certificate> cert);
                    X509Certificate(const std::vector<uint8_t>& buffer, const std::string& password);
                    X509Certificate(const std::string& fileName, const std::string& password);
                };
            }
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
