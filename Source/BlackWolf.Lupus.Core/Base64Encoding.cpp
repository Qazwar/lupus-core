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

#include "Base64Encoding.h"
#include "String.h"

namespace Lupus {
    namespace Text {

        String Base64Encoding::GetString(const Vector<U8>& buffer) const
        {
            return GetString(buffer, 0, buffer.size());
        }

        String Base64Encoding::GetString(const Vector<U8>& buffer, U32 offset, U32 size) const
        {
            if (offset > buffer.size()) {
                throw OutOfRange("offset");
            } else if (size > buffer.size() - offset) {
                throw OutOfRange("size");
            }

            // TODO: Impelement
            return "";
        }

        Vector<U8> Base64Encoding::GetBytes(const String& str) const
        {
            return GetBytes(str, 0, str.Length());
        }

        Vector<U8> Base64Encoding::GetBytes(const String& str, U32 offset, U32 size) const
        {
            if (offset > str.Length()) {
                throw OutOfRange("offset");
            } else if (size > str.Length() - offset) {
                throw OutOfRange("size");
            }

            // TODO: Implement
            return {};
        }
    }
}
