#pragma once

#include <boost/noncopyable.hpp>

#include "String.h"
#include "DataType.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Data {
        class LUPUSCORE_API DataColumn
        {
        public:

            DataColumn(const String&, DataType, int);
            virtual ~DataColumn() = default;

            virtual String Name() const NOEXCEPT;
            virtual DataType Type() const NOEXCEPT;
            virtual int Index() const NOEXCEPT;

        private:
            String mName;
            DataType mType;
            int mIndex;
        };
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
