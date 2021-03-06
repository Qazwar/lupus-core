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
#pragma once

namespace Lupus {
    namespace Data {
        enum class DataType {
            Boolean,
            Byte,
            Character,
            CharacterVarying,
            Date,
            DateTime,
            Decimal,
            DoublePrecision,
            Float,
            Integer,
            Integer8,
            Interval,
            Numeric,
            Real,
            Serial,
            Serial8,
            SmallFloat,
            SmallInt,
            Text,
            Unknown
        };
    }
}
