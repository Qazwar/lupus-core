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
#include <functional>
#include <BlackWolf.Lupus.Core/String.h>
#include <BlackWolf.Lupus.Core/Task.h>

namespace Lupus {
    namespace Data {
        class Parameter;
        class ITransaction;
        class IDataReader;

        class LUPUSDATA_API Command : public NonCopyable
        {
        public:

            virtual ~Command() = default;

            virtual Task<int> ExecuteNonQueryAsync() NOEXCEPT;
            virtual Task<Pointer<IDataReader>> ExecuteReaderAsync() NOEXCEPT;
            virtual Task<Vector<NameCollection<Any>>> ExecuteScalarAsync() NOEXCEPT;

            virtual void Text(const String&) NOEXCEPT = 0;
            virtual String& Text() NOEXCEPT = 0;
            virtual const String& Text() const NOEXCEPT = 0;
            virtual Vector<Pointer<Parameter>>& Parameters() NOEXCEPT = 0;
            virtual const Vector<Pointer<Parameter>>& Parameters() const NOEXCEPT = 0;

            virtual Pointer<Parameter> CreateParameter() NOEXCEPT = 0;
            virtual int ExecuteNonQuery() throw(SqlError) = 0;
            virtual Pointer<IDataReader> ExecuteReader() throw(SqlError) = 0;
            virtual Vector<NameCollection<Any>> ExecuteScalar() throw(SqlError) = 0;
            virtual bool Prepare() throw(SqlError) = 0;
        };
    }
}
