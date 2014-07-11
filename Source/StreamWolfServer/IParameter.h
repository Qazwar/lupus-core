#pragma once

#include <string>
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

#include "DataType.h"

namespace StreamWolf {
    namespace Data {
        class IParameter : public boost::noncopyable
        {
        public:

            virtual ~IParameter() = default;

            virtual DataType& DbType() const = 0;
            virtual void DbType(DataType) = 0;
            virtual bool& IsNullable() const = 0;
            virtual void IsNullable(bool) = 0;
            virtual std::string& Name() const = 0;
            virtual void Name(const std::string&) = 0;
            virtual boost::any& Value() const = 0;
            virtual void Value(const boost::any&) = 0;
        };
    }
}
