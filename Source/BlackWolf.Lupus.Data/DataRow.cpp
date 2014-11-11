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
#include "DataRow.h"
#include "DataColumn.h"

#include <algorithm>

using namespace std;

namespace Lupus {
    namespace Data {

        DataRow::DataRow(NameCollection<Any>& items)
        {
            mItems = move(items);

            for (auto& it : mItems) {
                mRefItems.push_back(&it.second);
            }
        }

        Any& DataRow::operator[](unsigned index)
        {
            if (index >= mRefItems.size()) {
                throw std::out_of_range("index");
            }

            return *mRefItems[index];
        }

        const Any& DataRow::operator[](unsigned index) const
        {
            if (index >= mRefItems.size()) {
                throw std::out_of_range("index");
            }

            return *mRefItems[index];
        }

        Any& DataRow::operator[](const String& str)
        {
            if (mItems.find(str) == end(mItems)) {
                throw std::invalid_argument("Key does not exist");
            }

            return mItems.at(str);
        }

        const Any& DataRow::operator[](const String& str) const
        {
            if (mItems.find(str) == end(mItems)) {
                throw std::invalid_argument("Key does not exist");
            }

            return mItems.at(str);
        }

        Any& DataRow::operator[](shared_ptr<DataColumn> column)
        {
            if (!column) {
                throw null_pointer("column");
            } else if (mItems.find(column->Name()) == end(mItems)) {
                throw std::invalid_argument("Key does not exist");
            }

            return mItems.at(column->Name());
        }

        const Any& DataRow::operator[](shared_ptr<DataColumn> column) const
        {
            if (!column) {
                throw null_pointer("column");
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

        NameCollection<Any> DataRow::Items() const
        {
            return mItems;
        }
    }
}
