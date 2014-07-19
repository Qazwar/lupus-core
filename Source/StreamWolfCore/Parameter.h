#pragma once

#include <string>
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

#include "Utility.h"
#include "DataType.h"

namespace StreamWolf {
    namespace Data {
        class SWC_API Parameter : public boost::noncopyable
        {
        public:

            Parameter() = default;
            Parameter(DataType, const boost::any&);
            virtual ~Parameter() = default;

            virtual DataType& DbType() NOEXCEPT;
            virtual const DataType& DbType() const NOEXCEPT;
            virtual void DbType(DataType) NOEXCEPT;

            virtual boost::any& Value() NOEXCEPT;
            virtual const boost::any& Value() const NOEXCEPT;
            virtual void Value(const boost::any&) NOEXCEPT;

        private:

            DataType mType;
            boost::any mValue;
        };
    }
}