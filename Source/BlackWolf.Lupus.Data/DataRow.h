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
#include <memory>
#include <BlackWolf.Lupus.Core/String.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Data {
        class DataColumn;

        class LUPUSDATA_API DataRow : public NonCopyable
        {
        public:

            explicit DataRow(NameCollection<Any>&);
            virtual ~DataRow() = default;

            virtual Any& operator[](unsigned) throw(OutOfRange);
            virtual const Any& operator[](unsigned) const throw(OutOfRange);

            virtual Any& operator[](const String&) throw(InvalidArgument);
            virtual const Any& operator[](const String&) const throw(InvalidArgument);

            virtual Any& operator[](Pointer<DataColumn>) throw(InvalidArgument, NullPointer);
            virtual const Any& operator[](Pointer<DataColumn>) const throw(InvalidArgument, NullPointer);

            virtual U32 Count() const NOEXCEPT;
            virtual bool IsEmpty() const NOEXCEPT;
            virtual NameCollection<Any> Items() const NOEXCEPT;

        private:

            NameCollection<Any> mItems;
            Vector<Any*> mRefItems;
        };
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
