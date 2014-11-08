#pragma once

#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

#include "Utility.h"
#include "DataType.h"

namespace Lupus {
    namespace Data {
        class LUPUSCORE_API IDataReader : public boost::noncopyable
        {
        public:
            
            virtual ~IDataReader() = default;
            
            virtual int Depth() const NOEXCEPT = 0;
            virtual int FieldCount() const NOEXCEPT = 0;
            virtual String ColumnName(int) const NOEXCEPT = 0;
            virtual int ColumnNumber(const String&) const NOEXCEPT = 0;
            virtual DataType Type(int) const NOEXCEPT = 0;
            virtual boost::any Value(int) const NOEXCEPT = 0;
            virtual bool IsNull(int) const NOEXCEPT = 0;
            virtual bool NextResult() NOEXCEPT = 0;
        };
    }
}
