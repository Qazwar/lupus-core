#pragma once

#include <string>
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

#include "DataType.h"

namespace StreamWolf {
    namespace Data {
        class Parameter : public boost::noncopyable
        {
        public:

            Parameter() = default;
            Parameter(DataType, const boost::any&);
            virtual ~Parameter() = default;

            virtual DataType& DbType();
            virtual const DataType& DbType() const;
            virtual void DbType(DataType);

            virtual boost::any& Value();
            virtual const boost::any& Value() const;
            virtual void Value(const boost::any&);

        private:

            DataType mType;
            boost::any mValue;
        };
    }
}
