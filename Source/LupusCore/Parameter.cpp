#include "Parameter.h"

namespace Lupus {
    namespace Data {
        Parameter::Parameter(DataType type, const boost::any& value)
        {
            mType = type;
            mValue = value;
        }

        DataType& Parameter::DbType()
        {
            return mType;
        }

        const DataType& Parameter::DbType() const
        {
            return mType;
        }

        void Parameter::DbType(DataType type)
        {
            mType = type;
        }

        boost::any& Parameter::Value()
        {
            return mValue;
        }

        const boost::any& Parameter::Value() const
        {
            return mValue;
        }

        void Parameter::Value(const boost::any& value)
        {
            mValue = value;
        }
    }
}
