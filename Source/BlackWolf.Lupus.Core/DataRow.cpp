#include "DataRow.h"
#include "DataColumn.h"

#include <algorithm>

using namespace std;

namespace Lupus {
    namespace Data {

        DataRow::DataRow(unordered_map<String, boost::any>& items)
        {
            mItems = move(items);

            for (auto& it : mItems) {
                mRefItems.push_back(&it.second);
            }
        }

        boost::any& DataRow::operator[](unsigned i)
        {
            if (i >= mRefItems.size()) {
                throw std::out_of_range("i exceeds size of items");
            }

            return *mRefItems[i];
        }

        const boost::any& DataRow::operator[](unsigned i) const
        {
            if (i >= mRefItems.size()) {
                throw std::out_of_range("i exceeds size of items");
            }

            return *mRefItems[i];
        }

        boost::any& DataRow::operator[](const String& str)
        {
            if (mItems.find(str) == end(mItems)) {
                throw std::invalid_argument("Key does not exist");
            }

            return mItems.at(str);
        }

        const boost::any& DataRow::operator[](const String& str) const
        {
            if (mItems.find(str) == end(mItems)) {
                throw std::invalid_argument("Key does not exist");
            }

            return mItems.at(str);
        }

        boost::any& DataRow::operator[](shared_ptr<DataColumn> column)
        {
            if (!column) {
                throw null_pointer();
            } else if (mItems.find(column->Name()) == end(mItems)) {
                throw std::invalid_argument("Key does not exist");
            }

            return mItems.at(column->Name());
        }

        const boost::any& DataRow::operator[](shared_ptr<DataColumn> column) const
        {
            if (!column) {
                throw null_pointer();
            } else if (mItems.find(column->Name()) == end(mItems)) {
                throw std::invalid_argument("Key does not exist");
            }

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

        unordered_map<String, boost::any> DataRow::Items() const
        {
            return mItems;
        }
    }
}
