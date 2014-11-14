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

            virtual Any& operator[](unsigned) throw(std::out_of_range);
            virtual const Any& operator[](unsigned) const throw(std::out_of_range);

            virtual Any& operator[](const String&) throw(std::invalid_argument);
            virtual const Any& operator[](const String&) const throw(std::invalid_argument);

            virtual Any& operator[](std::shared_ptr<DataColumn>) throw(std::invalid_argument, null_pointer);
            virtual const Any& operator[](std::shared_ptr<DataColumn>) const throw(std::invalid_argument, null_pointer);

            virtual size_t Count() const NOEXCEPT;
            virtual bool IsEmpty() const NOEXCEPT;
            virtual NameCollection<Any> Items() const NOEXCEPT;

        private:

            NameCollection<Any> mItems;
            std::vector<Any*> mRefItems;
        };
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
