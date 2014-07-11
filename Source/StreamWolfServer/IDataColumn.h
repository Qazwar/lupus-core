#pragma once

#include <string>
#include <boost/noncopyable.hpp>

#include "DataType.h"

namespace StreamWolf {
    namespace Data {
        class IDataColumn
        {
        public:

            virtual ~IDataColumn() = default;

            virtual std::string Name() const = 0;
            virtual DataType Type() const = 0;
            virtual int Index() const = 0;
        };
    }
}
