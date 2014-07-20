#pragma once

#include <string>
#include <boost/noncopyable.hpp>

#include "Utility.h"
#include "DataType.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
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

#ifdef _MSC_VER
#pragma warning(pop)
#endif
