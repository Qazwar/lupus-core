/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Lupus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lupus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lupus. If not, see <http://www.gnu.org/licenses/>.
 */
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