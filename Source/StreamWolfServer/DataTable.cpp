#include "DataTable.h"
#include "DataColumn.h"
#include "DataRow.h"
#include "IDataReader.h"

using namespace std;

namespace StreamWolf {
    namespace Data {
        void DataTable::Load(shared_ptr<IDataReader> reader)
        {
            if (reader->Depth() == 0) {
                return;
            }

            for (int i = 0; i < reader->FieldCount(); i++) {
                mColumns.push_back(make_shared<DataColumn>(
                    reader->ColumnName(i), reader->Type(i), i
                ));
            }

            do {
                unordered_map<string, boost::any> row;

                for (int i = 0; i < reader->FieldCount(); i++) {
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
