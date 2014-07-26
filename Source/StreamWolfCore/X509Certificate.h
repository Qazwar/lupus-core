#pragma once

#include <boost/noncopyable.hpp>

#include "Utility.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            namespace X509Certificates {
                class LUPUS_API X509Certificate : public boost::noncopyable
                {

                };
            }
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
