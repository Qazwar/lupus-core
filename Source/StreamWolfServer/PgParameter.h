#pragma once

#include "IParameter.h"

namespace StreamWolf {
    namespace Data {
        namespace Postgres {
            class Parameter : public IParameter
            {
            public:

                virtual ~Parameter();

                virtual DataType& DbType() = 0;
                virtual const DataType& DbType() const = 0;
                virtual void DbType(DataType) = 0;

                virtual bool& IsNullable() = 0;
                virtual const bool& IsNullable() const = 0;
                virtual void IsNullable(bool) = 0;

                virtual std::string& Name() = 0;
                virtual const std::string& Name() const = 0;
                virtual void Name(const std::string&) = 0;

                virtual boost::any& Value() = 0;
                virtual const boost::any& Value() const = 0;
                virtual void Value(const boost::any&) = 0;
            };
        }
    }
}
