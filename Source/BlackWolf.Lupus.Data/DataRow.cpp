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
#include "DataRow.h"
#include "DataColumn.h"

#include <algorithm>



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
                throw OutOfRange("index");
            }

            return *mRefItems[index];
        }

        const Any& DataRow::operator[](unsigned index) const
        {
            if (index >= mRefItems.size()) {
                throw OutOfRange("index");
            }

            return *mRefItems[index];
        }

        Any& DataRow::operator[](const String& str)
        {
            if (mItems.find(str) == end(mItems)) {
                throw InvalidArgument("Key does not exist");
            }

            return mItems.at(str);
        }

        const Any& DataRow::operator[](const String& str) const
        {
            if (mItems.find(str) == end(mItems)) {
                throw InvalidArgument("Key does not exist");
            }

            return mItems.at(str);
        }

        Any& DataRow::operator[](Pointer<DataColumn> column)
        {
            if (!column) {
                throw NullPointer("column");
            } else if (mItems.find(column->Name()) == end(mItems)) {
                throw InvalidArgument("Key does not exist");
            }

            return mItems.at(column->Name());
        }

        const Any& DataRow::operator[](Pointer<DataColumn> column) const
        {
            if (!column) {
                throw NullPointer("column");
            } else if (mItems.find(column->Name()) == end(mItems)) {
                throw InvalidArgument("Key does not exist");
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
