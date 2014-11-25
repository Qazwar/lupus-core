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
#pragma once

#include "Utility.h"
#include <vector>
#include <memory>
#include <BlackWolf.Lupus.Core/String.h>


#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Data {
        class IDataReader;
        class DataColumn;
        class DataRow;

        class LUPUSDATA_API DataTable : public NonCopyable
        {
        public:

            virtual ~DataTable() = default;

            virtual void Load(Pointer<IDataReader>);
            virtual Vector<Pointer<DataRow>> Rows() const NOEXCEPT;
            virtual U32 RowCount() const NOEXCEPT;
            virtual Vector<Pointer<DataColumn>> Columns() const NOEXCEPT;
            virtual U32 ColumnCount() const NOEXCEPT;
            virtual Vector<Pointer<DataRow>> Fetch(unsigned, unsigned) const NOEXCEPT;

        private:

            Vector<Pointer<DataColumn>> mColumns;
            Vector<Pointer<DataRow>> mRows;
        };
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
