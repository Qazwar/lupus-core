#pragma once

#include <string>
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

#include "Utility.h"
#include "DataType.h"

namespace StreamWolf {
    namespace Data {
        class SWC_API IDataReader : public boost::noncopyable
        {
        public:
            
            virtual ~IDataReader() = default;
            
            virtual int Depth() const NOEXCEPT = 0;
            virtual int FieldCount() const NOEXCEPT = 0;
            virtual std::string ColumnName(int) const NOEXCEPT = 0;
            virtual int ColumnNumber(const std::string&) const NOEXCEPT = 0;
            virtual DataType Type(int) const NOEXCEPT = 0;
            virtual boost::any Value(int) const NOEXCEPT = 0;
            virtual bool IsNull(int) const NOEXCEPT = 0;
            virtual bool NextResult() NOEXCEPT = 0;
        };
    }
}
