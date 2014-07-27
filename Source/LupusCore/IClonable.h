#pragma once

#include "Utility.h"
#include <memory>

namespace Lupus {
    class LUPUS_API IClonable
    {
    public:
        virtual ~IClonable() = default;
        virtual std::shared_ptr<IClonable> Clone() const = 0;
    };
}
