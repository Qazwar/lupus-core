#pragma once

#include <string>
#include <boost/noncopyable.hpp>

#include "DataType.h"

namespace StreamWolf {
    namespace Data {
        class DataColumn
        {
        public:

            DataColumn(const std::string&, DataType, int);
            virtual ~DataColumn() = default;

            virtual std::string Name() const;
            virtual DataType Type() const;
            virtual int Index() const;

        private:

            std::string mName;
            DataType mType;
            int mIndex;
        };
    }
}
