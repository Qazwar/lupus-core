#include "DataRow.h"
#include "DataColumn.h"

#include <algorithm>

using namespace std;

namespace StreamWolf {
    namespace Data {

        DataRow::DataRow(unordered_map<string, boost::any>& items)
        {
            mItems = move(items);

            for (auto& it : mItems) {
                mRefItems.push_back(&it.second);
            }
        }

        boost::any& DataRow::operator[](unsigned i)
        {
            return *mRefItems[i];
        }

        const boost::any& DataRow::operator[](unsigned i) const
        {
            return *mRefItems[i];
        }

        boost::any& DataRow::operator[](const string& str)
        {
            return mItems.at(str);
        }

        const boost::any& DataRow::operator[](const string& str) const
        {
            return mItems.at(str);
        }

        boost::any& DataRow::operator[](shared_ptr<DataColumn> column)
        {
            return mItems.at(column->Name());
        }

        const boost::any& DataRow::operator[](shared_ptr<DataColumn> column) const
        {
            return mItems.at(column->Name());
        }

        size_t DataRow::Count() const
        {
            return mItems.size();
        }

        bool DataRow::IsEmpty() const
        {
            return mItems.empty();
        }

        unordered_map<string, boost::any> DataRow::Items() const
        {
            return mItems;
        }
    }
}
