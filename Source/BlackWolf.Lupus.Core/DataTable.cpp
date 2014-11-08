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
#include "DataTable.h"
#include "DataColumn.h"
#include "DataRow.h"
#include "IDataReader.h"

using namespace std;

namespace Lupus {
    namespace Data {
        void DataTable::Load(shared_ptr<IDataReader> reader)
        {
            if (reader->Depth() == 0) {
                return;
            }

            const int fieldCount = reader->FieldCount();

            for (int i = 0; i < fieldCount; i++) {
                mColumns.push_back(make_shared<DataColumn>(
                    reader->ColumnName(i), reader->Type(i), i
                ));
            }

            do {
                unordered_map<String, boost::any> row;

                for (int i = 0; i < fieldCount; i++) {
                    row[reader->ColumnName(i)] = reader->Value(i);
                }

                mRows.push_back(make_shared<DataRow>(row));
            } while (reader->NextResult());
        }

        vector<shared_ptr<DataRow>> DataTable::Rows() const
        {
            return mRows;
        }
        
        size_t DataTable::RowCount() const
        {
            return mRows.size();
        }
        
        vector<shared_ptr<DataColumn>> DataTable::Columns() const
        {
            return mColumns;
        }

        size_t DataTable::ColumnCount() const
        {
            return mColumns.size();
        }
        
        vector<shared_ptr<DataRow>> DataTable::Fetch(unsigned row, unsigned count) const
        {
            if (row + count > mRows.size()) {
                return vector<shared_ptr<DataRow>>();
            }

            auto it = begin(mRows) + row;

            return vector<shared_ptr<DataRow>>(it, it + count);
        }
    }
}
