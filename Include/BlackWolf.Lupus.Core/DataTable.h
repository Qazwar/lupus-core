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

#include <vector>
#include <memory>
#include <boost/noncopyable.hpp>

#include "String.h"


#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Data {
        class IDataReader;
        class DataColumn;
        class DataRow;

        class LUPUSCORE_API DataTable : public boost::noncopyable
        {
        public:

            virtual ~DataTable() = default;

            virtual void Load(std::shared_ptr<IDataReader>);
            virtual std::vector<std::shared_ptr<DataRow>> Rows() const NOEXCEPT;
            virtual size_t RowCount() const NOEXCEPT;
            virtual std::vector<std::shared_ptr<DataColumn>> Columns() const NOEXCEPT;
            virtual size_t ColumnCount() const NOEXCEPT;
            virtual std::vector<std::shared_ptr<DataRow>> Fetch(unsigned, unsigned) const NOEXCEPT;

        private:

            std::vector<std::shared_ptr<DataColumn>> mColumns;
            std::vector<std::shared_ptr<DataRow>> mRows;
        };
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
