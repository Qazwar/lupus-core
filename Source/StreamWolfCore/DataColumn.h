#pragma once

#include <string>
#include <boost/noncopyable.hpp>

#include "Utility.h"
#include "DataType.h"

namespace StreamWolf {
    namespace Data {
        class SWC_API DataColumn
        {
        public:

            DataColumn(const std::string&, DataType, int);
            virtual ~DataColumn() = default;

            virtual std::string Name() const NOEXCEPT;
            virtual DataType Type() const NOEXCEPT;
            virtual int Index() const NOEXCEPT;

        private:

            std::string mName;
            DataType mType;
            int mIndex;
        };
    }
}
