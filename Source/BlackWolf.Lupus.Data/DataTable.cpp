/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "DataTable.h"
#include "DataColumn.h"
#include "DataRow.h"
#include "IDataReader.h"



namespace Lupus {
    namespace Data {
        void DataTable::Load(Pointer<IDataReader> reader)
        {
            if (reader->Depth() == 0) {
                return;
            }

            const int fieldCount = reader->FieldCount();

            for (int i = 0; i < fieldCount; i++) {
                mColumns.push_back(MakePointer<DataColumn>(
                    reader->ColumnName(i), reader->Type(i), i
                ));
            }

            do {
                NameCollection<Any> row;

                for (int i = 0; i < fieldCount; i++) {
                    row[reader->ColumnName(i)] = reader->Value(i);
                }

                mRows.push_back(MakePointer<DataRow>(row));
            } while (reader->NextResult());
        }

        Vector<Pointer<DataRow>> DataTable::Rows() const
        {
            return mRows;
        }
        
        size_t DataTable::RowCount() const
        {
            return mRows.size();
        }
        
        Vector<Pointer<DataColumn>> DataTable::Columns() const
        {
            return mColumns;
        }

        size_t DataTable::ColumnCount() const
        {
            return mColumns.size();
        }
        
        Vector<Pointer<DataRow>> DataTable::Fetch(unsigned row, unsigned count) const
        {
            if (row + count > mRows.size()) {
                return Vector<Pointer<DataRow>>();
            }

            auto it = begin(mRows) + row;

            return Vector<Pointer<DataRow>>(it, it + count);
        }
    }
}
