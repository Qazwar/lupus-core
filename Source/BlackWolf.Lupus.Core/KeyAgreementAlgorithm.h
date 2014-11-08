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
            // TODO: Schnittstelle ausbauen und Klasse implementieren.
            class LUPUSCORE_API KeyExchangeAlgorithm : public IClonable<KeyExchangeAlgorithm>, public boost::noncopyable
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
