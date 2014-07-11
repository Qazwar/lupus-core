#pragma once

#include <string>
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

#include "DataType.h"

namespace StreamWolf {
    namespace Data {
        class IDataReader : public boost::noncopyable
        {
        public:
            
            virtual ~IDataReader() = default;
            
            virtual int Depth() const = 0;
            virtual int FieldCount() const = 0;
            virtual std::string ColumnName(int) const = 0;
            virtual int ColumnNumber(const std::string&) const = 0;
            virtual DataType DataType(int) const = 0;
            virtual boost::any Value(int) const = 0;
            virtual bool IsNull(int) const = 0;
            virtual bool NextResult() const = 0;
        };
    }
}
