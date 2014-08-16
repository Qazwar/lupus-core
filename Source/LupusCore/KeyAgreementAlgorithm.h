#pragma once

#include "Utility.h"
#include "IClonable.h"
#include <boost/noncopyable.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            class LUPUS_API KeyExchangeAlgorithm : public IClonable, public boost::noncopyable
            {
            public:

                virtual ~KeyExchangeAlgorithm() = default;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
